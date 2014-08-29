/*
MORSE CODE - CodeEval Easy challenge

CHALLENGE DESCRIPTION:

You have received a text encoded with Morse code and want to decode it.

INPUT SAMPLE:

Your program should accept as its first argument a path to a filename.
Input example is the following:

.- ...- ..--- .-- .... .. . -.-. -..-  ....- .....
-... .... ...--

Each letter is separated by a space char, each word is separated by 2 space chars.

OUTPUT SAMPLE:

Print out decoded words. E.g.

AV2WHIECX 45
BH3

You program has to support letters and digits only.

*/

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

#include <cassert>

#ifndef DEBUG
#define NDEBUG
#endif // DEBUG

using namespace std;

void init_map(unordered_map<string,char> & morse_map)
{
	morse_map.insert (
        {
        { ".-",		'A' },
        { "-...",	'B' },
        { "-.-.",	'C' },
        { "-..",	'D' },
        { ".",		'E' },
        { "..-.",	'F' },
        { "--.",	'G' },
        { "....",	'H' },
        { "..",		'I' },
        { ".---",	'J' },
        { "-.-",	'K' },
        { ".-..",	'L' },
        { "--",		'M' },
        { "-.",		'N' },
        { "---",	'O' },
        { ".--.",	'P' },
        { "--.-",	'Q' },
        { ".-.",	'R' },
        { "...",	'S' },
        { "-",		'T' },
        { "..-",	'U' },
        { "...-",	'V' },
        { ".--",	'W' },
        { "-..-",	'X' },
        { "-.--",	'Y' },
        { "--..",	'Z' },
        { ".----",	'1' },
        { "..---",	'2' },
        { "...--",	'3' },
        { "....-",	'4' },
        { ".....",	'5' },
        { "-....",	'6' },
        { "--...",	'7' },
        { "---..",	'8' },
        { "----.",	'9' },
        { "-----",	'0' },
        }
    );
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
            cout << "usage: " << argv[0] << "<filename>\n";
            return 1;
    }

    unordered_map<string,char> morse_map;
    init_map(morse_map);

    ifstream ifs(argv[1]);
    string line;

    while (getline(ifs, line))
    {
        // Parsing a line of morse is different b/c words are separated by two blanks.
        unsigned pos = 0;
        while (line[pos] == ' ') pos++; // skip (unexpected) leading whitespace
        
        while (true) // see condition for breaking out of this loop
        {    
            unsigned pos2 = line.find_first_of(' ', pos); // returns npos if null found,
            const string m = line.substr(pos, pos2-pos);  // but substr still works ok
            const char c = morse_map.find(m)->second;
            cout << c;
            if (pos2 == (unsigned) string::npos) { // done with this line
                cout << endl;
                break;
            }
            else {
                pos = pos2;
                assert(line[pos++] == ' ');
                if (line[pos] == ' ') { // word boundary - two blanks
                    cout << ' ';
                    ++pos;
                }
            }
        }
    } // while getline
}

// EOF
