// STRING SUBSTITUTION - CodeEval Hard challenge
// CHALLENGE DESCRIPTION:
// 
// Credits: This challenge was contributed by Sam McCoy 
// 
// Given a string S, and a list of strings of positive length,
// F1,R1,F2,R2,...,FN,RN, proceed to find in order the occurrences
// (left-to-right) of Fi in S and replace them with Ri. All strings are
// over alphabet { 0, 1 }. Searching should consider only contiguous pieces
// of S that have not been subj to replacements on prior iterations. An
// iteration of the algorithm should not write over any previous
// replacement by the algorithm.
// 
// INPUT SAMPLE:
// 
// Your program should accept as its first argument a path to a filename.
// Each line in this file is one test case. Each test case will contain a
// string, then a semicolon and then a list of comma separated strings.
// E.g.
// 
// 10011011001;0110,1001,1001,0,10,11
// 
// OUTPUT SAMPLE:
// 
// For each line of input, print out the string after substitutions have been made.eg.
// 
// 11100110
// 
// For the curious, here are the transitions for the above example:
// 10011011001 => 10100111001 [replacing 0110 with 1001] => 10100110
// [replacing 1001 with 0] => 11100110 [replacing 10 with 11]. So the
// answer is 11100110
// 
// =====================================================================
// Gotchas:
// 1. If the pattern sought is not present in the subject, move on to
// the next (pattern or line).
// 2. The pattern may occur multiple times in the subject and must be
// replaced each time.


#include <iostream>
#include <fstream>
#include <sstream>

#include <algorithm>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "usage: " << argv[0] << "<filename>\n";
        return 1;
    }

    ifstream ifs(argv[1]);
    string line;

    while (getline(ifs, line))
    {
        // first nuke all the commas 
        replace(line.begin(), line.end(), ',', ' ');
        // now nuke the semicolon
        line[line.find_first_of(';')] = ' ';
#ifdef DEBUG
        cout << "======" << line << endl;
#endif
        istringstream iss(line);
        string subj;
        iss >> subj;
#ifdef DEBUG
        cout << subj << endl;
#endif
        string pat, repl;
        while (iss >> pat) {
            iss >> repl;
            // By negating the elements of the replacement, we ensure we
            // will obey the mandate to not consider decoded chars for
            // for further replacements in subj.  We could have used a
            // parallel array or vector or even a map instead, but this
            // is easy and straightforward except for printing debug output.
            for (unsigned i = 0; i < repl.length(); ++i) {
                repl[i] = -repl[i];
            }
#ifdef DEBUG
            cout << "pattern: " << pat << ", replacement(raw): " << repl << endl;
#endif
            size_t pindex;
            while ( (pindex = subj.find(pat) ) != string::npos) {
                // found (another) match
                subj.erase(pindex, pat.length());
                subj.insert(pindex, repl);
#ifdef DEBUG
                cout << "subj after replacement: ";
                for (unsigned j = 0; j < subj.length(); ++j) {
                    cout << char(abs(subj[j]));
                }
                cout << endl;
#endif
            }
        }
        for (unsigned j = 0; j < subj.length(); ++j) {
            cout << char(abs(subj[j]));
        }
        cout << endl;
    }
}

