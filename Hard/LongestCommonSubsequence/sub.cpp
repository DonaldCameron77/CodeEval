/*
LONGEST COMMON SUBSEQUENCE
CHALLENGE DESCRIPTION:

You are given two sequences. Write a program to determine the longest
common subsequence between the two strings (each string can have a
maximum length of 50 characters). NOTE: This subsequence need not be
contiguous. The input file may contain empty lines, these need to be
ignored.

INPUT SAMPLE:

The first argument will be a path to a filename that contains two
strings per line, semicolon delimited. You can assume that there is only
one unique subsequence per test case. E.g.

XMJYAUZ;MZJAWXU

OUTPUT SAMPLE:

The longest common subsequence. Ensure that there are no trailing empty
spaces on each line you print. E.g.

MJAU
*/

// This version uses top-down Dynamic Programming, i.e., memoization,
// to avoid the recomputations and consequent extreme speed penalty
// of a pure recursive solution

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void print_lcs( string & S, string & T )
{
    int M[S.size() + 1][T.size() + 1]; // memoization matrix
    for (unsigned i = 0; i <= S.size(); ++i) {
        M[i][0] = 0;
    }
    for (unsigned j = 0; j <= T.size(); ++j) {
        M[0][j] = 0;
    }

    for (int i = 1; i <= S.size(); ++i) {
        for (int j = 1; j <= T.size(); ++j) {
            if (S[i-1] == T[j-1]) {
                M[i][j] = M[i-1][j-1] + 1;
            }
            else {
                M[i][j] = max(M[i][j-1], M[i-1][j]);
            }
        }
    }

#ifdef DEBUG
    // DEBUG LOOP(s)
    for (int i = 0; i <= S.size(); ++i) {
        for (int j = 0; j <= T.size(); ++j) {
            cout << M[i][j] << " ";
        }
        cout << endl;
    }
#endif // DEBUG

    string res;
    int x = S.size();
    int y = T.size();

    while (x > 0 && y > 0) {
        if (S[x-1] == T[y-1]) {
            res += S[x-1];
            --x, --y;
        }
        else {
            if (M[x][y] == M[x-1][y])
                --x; 
            else
                --y; 
        }
    }

    for (int i = res.size() - 1; i >= 0; --i) {
        cout << res[i];
    }
    cout << endl;
}

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
        if (line.empty())
            continue;
        unsigned semipos = line.find(';');
        string S = line.substr(0, semipos);
        string T = line.substr(semipos+1);
        print_lcs(S, T);
    }
}

// EOF
