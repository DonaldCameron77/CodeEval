/*
ARRAY ABSURDITY - CodeEval Moderate challenge
CHALLENGE DESCRIPTION:

Imagine we have an immutable array of size N which we know to be filled
with integers ranging from 0 to N-2, inclusive. Suppose we know that the
array contains exactly one duplicated entry and that duplicate appears
exactly twice. Find the duplicated entry. (For bonus points, ensure your
solution has constant space and time proportional to N)

INPUT SAMPLE:

Your program should accept as its first argument a path to a filename.
Each line in this file is one test case. Ignore all empty lines. Each
line begins with a positive integer(N) i.e. the size of the array, then
a semicolon followed by a comma separated list of positive numbers
ranging from 0 to N-2, inclusive. i.e eg.

5;0,1,2,3,0
20;0,1,10,3,2,4,5,7,6,8,11,9,15,12,13,4,16,18,17,14

OUTPUT SAMPLE:

Print out the duplicated entry, each one on a new line eg

0
4

*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <set>

using namespace std;

/*
DONT DO IT THIS WAY.

FIGURE OUT WHAT THE SUM OF N INTEGERS FROM 0 TO N-2 SHOULD BE

ADD UP THE EXISTING INTEGERS.

THE EXCESS AMOUNT/2 IS THE OFFENDER

BUT BEWARE OF ZERO BEING DUPLICATED!!!!  
*/

int main(int argc, char *argv[])
{

    if (argc != 2) {
        cout << "usage: " << argv[0] << "<filename>\n";
        return 1;
    }

    ifstream inps(argv[1]);
    string linebuf;
    set<int> aset;

    while (getline(inps, linebuf))
    {
        size_t listpos = linebuf.find(';') + 1;
        string alist = linebuf.substr(listpos);
        istringstream als(alist);
        int nextval;	
        aset.clear();
        
        while (als >> nextval) {
            if (aset.count(nextval)) {
                // har har gotcha
                cout << nextval;
                break;
            }
            aset.insert(nextval);
            als.ignore(); // skip over trailing comma
        }
                
        cout << endl; // ensure blank line when no match found
    } // while getline
}

