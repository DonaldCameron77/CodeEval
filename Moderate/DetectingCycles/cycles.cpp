/*
DETECTING CYCLES - CodeEval Moderate challenge

CHALLENGE DESCRIPTION:

Given a sequence, write a program to detect cycles within it.

INPUT SAMPLE:

Your program should accept as its first argument a path to a filename
containing a sequence of numbers (space delimited). The file can have
multiple such lines. E.g

2 0 6 3 1 6 3 1 6 3 1
3 4 8 0 11 9 7 2 5 6 10 1 49 49 49 49
1 2 3 1 2 3 1 2 3

OUTPUT SAMPLE:

Print to stdout the first cycle you find in each sequence. Ensure that
there are no trailing empty spaces on each line you print. E.g.

6 3 1
49
1 2 3

Constrains: 

The elements of the sequence are integers in range [0, 99] 
The length of the sequence is in range [0, 50]

=======================================================================

Some coding notes:

Variables:
-- s: index in n of leftmost item
-- k: span of potential cycle: i.e., we want to know if the sublist
			n[s]..n[s+k] matches n[s+k+1]..n[s+2k+1]
-- t: for clarity we will let t be assigned s+k+1

Notice that for a given s, no sequence can be longer than
(n.size() - s)/2

Note: for a valid cycle, the repetition must be adjacent, i.e.,
n[s .. s+k] matches n[s+k+1 .. s+2k+1], IOW s+k+1 == t

Note: the program should print the first cycle and advance to the next line.
  E.g., for  2 3 1 2 3 4 5 6 1 2 3 1 2 3 4 5 6 the answer is 1 2 3.

*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
// #include <algorithm>

using namespace std;

int main(int argc, char *argv[]) {

    if (argc != 2) {
        cout <<"usage: "<< argv[0] <<" <filename>\n";
        return 1;
    }

    ifstream ifs(argv[1]);
    string line;
    vector<int> n;

    while (getline(ifs, line)) {
        istringstream inps(line);
        if (line.size() == 0) {
            continue;
        }

        n.clear();
        int nxtint;
        while (inps >> nxtint) { // collect the ints on current input line
            n.push_back(nxtint);
        }

#ifdef DEBUG
        for (int i = 0; i < n.size(); i++)
            cout << n[i] << " ";
        cout << endl;
#endif

        // The basic concept: find s and t such that elements of n,
        // n[s]..n[t-1] match one-for-one n[t]..n[2t-s],
        // (with t >= s+2 ?? UM, NO, see above for 49 49 49 49,
        // they think the answer is 49, so the REAL constraint is
        // t >= s+1, or simply t > s
        for (int s = 0; s <= (int)n.size() - 4; s++) { 
            // for any s, t cannot be greater than half the
            // distance from s to the end of the vector n.
            // I.e., t must be <= s + (n.size() - s)/2 which is equivalent to
            const int tmax = (s + n.size()) / 2; 
            for (int t = s+1; t <= tmax; t++) {
                if (n[s] == n[t]) { // leftmost entries match
                    int k = 1;
                    while (s+k < t && n[s+k] == n[t+k]) {
                        k++;
                    }		

                    if (s + k == t) {
#ifdef DEBUG
                        cout << "found cycle at s = " << s << ", t = "
                                << t << ", k = " << k << endl;
                        cout << "Input line was ";
                        for (int i = 0; i < n.size(); i++) {
                            cout << n[i] << " ";
                        }
                        cout << endl;
#endif // DEBUG

                        cout << n[s];
                        for (int i = s+1; i < s+k; i++) {
                            cout << " " << n[i];
                        }
                        cout << endl;
                        goto done; // The cleanest, if politically incorrect, way to break
                           // out of two nested loops, though a Boolean could be
                           // used as for loop condition (increasing clutter)
                    }
                } // leftmost entries match
            } // for t
        } // for s

done: ;
    } // while getline

}
