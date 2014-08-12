/*
FIRST NON-REPEATED CHARACTER - CodeEval Moderate challenge

CHALLENGE DESCRIPTION:

Write a program to find the first non repeated character in a string.

INPUT SAMPLE:

The first argument will be a path to a filename containing strings. E.g.

yellow
tooth

OUTPUT SAMPLE:

Print to stdout, the first non repeating character, one per line. E.g.

y
h

*/
// Two passes.  Pass one: record frequencies of each character seen.
// Pass two: traverse input in given order, and look up frequency
// of each element (character) of input.
// Xi Sisu cleverly used a Vector, but can we do better spacewise with Map?

#include <iostream>
#include <fstream>
#include <map>

using namespace std;

int main(int argc, char *argv[]) {

    if (argc != 2) {
        cout << "usage: " << argv[0] << "<filename>\n";
        return 1;
    }

    ifstream infs(argv[1]);
    string line;
    map<char, int> freq;

    while (getline(infs, line))
    {
        freq.clear();

        for (unsigned i = 0; i < line.size(); i++) {
            char cur = line[i];
            freq[cur] += 1; // just learned map operator [] will instantiate a new
                            // entry if cur not present in keys, and will set its value
                            // to zero (at least in the case of integer values) - kewl!
        }
        
        for (unsigned i = 0; i < line.size(); i++) {
            char cur = line[i];
            if (freq[cur] == 1) {
                cout << cur;
                break;
            }
        }
        cout << endl;
    } // while getline
}

