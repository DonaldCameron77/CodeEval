/* HIDDEN DIGITS - CodeEval challenge

CHALLENGE DESCRIPTION:

In this challenge you're given a random string containing hidden and
visible digits. The digits are hidden behind lower case latin letters as
follows: 0 is behind 'a', 1 is behind ' b ' etc., 9 is behind 'j'. Any
other symbol in the string means nothing and has to be ignored. So the
challenge is to find all visible and hidden digits in the string and
print them out in order of their appearance.

INPUT SAMPLE:

Your program should accept as its first argument a path to a filename.
Each line in this file contains a string. You may assume that there will
be no white spaces inside the string. E.g.

p 
Xa,}A#5N}{xOBwYBHIlH,#W
(ABW>'yy^'M{X-K}q,
6240488

OUTPUT SAMPLE:

For each test case print out all visible and hidden digits in order of
their appearance. Print out NONE in case there [are] no digits in the
string. E.g.

012345678
05
NONE
6240488

*/

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "usage: " << argv[0] << "<filename>\n";
        return 1;
    }

    ifstream inps(argv[1]);
    string instr;
    const string searchstring("0123456789abcdefghij");

    while (getline(inps, instr))
    {
        string outstr;
        unsigned long foundpos = instr.find_first_of(searchstring);

        while (foundpos != string::npos) {
            char c = instr[foundpos];
            if (c >= 'a' && c <= 'j') {
                c = (c - 'a' + '0');
            }
            outstr += c; // appends
            foundpos = instr.find_first_of(searchstring, foundpos+1);
        }
        
        if (outstr.empty())
            cout << "NONE";
        else
            // for (string::iterator it=outstr.begin(); it!=outstr.end(); ++it) {
            for (auto it=outstr.begin(); it!=outstr.end(); ++it) {
                cout << *it;
            }
        cout << endl;
    }
}


