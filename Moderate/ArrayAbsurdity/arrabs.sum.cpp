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
/*
    Note: the previous submittal used what was in effect a bitarray
    to find the duplicate element.  This implementation is not hugely
    faster, but is O(1) in space via summing the elements in the
    list.  Since we know the sum for 0,1,2,..,n-1,n (via
    the formula ( n * (n + 1) )/2, we can compare the computed
    value with the actual sum.  The difference is the repeated
    element (which could be zero(!)).
*/

#include <iostream>
#include <fstream>
#include <sstream>
// #include <set>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "usage: " << argv[0] << "<filename>\n";
        return 1;
    }

    ifstream inps(argv[1]);
    string linebuf;

    while (getline(inps, linebuf))
    {
        size_t listpos = linebuf.find(';') + 1;
        string alist = linebuf.substr(listpos);
        istringstream als(alist);
        int nextval;	
        unsigned sum = 0, count = 0;
        
        while (als >> nextval) {
            sum += nextval;
            ++ count;
            als.ignore(); // skip over trailing comma
        }

        // sum of 1, 2, ... k (and 0, 1, ..., k)
        // is ( k * (k + 1)) / 2
        // Since count is k+2 we have to decrement it;
        count -= 2;
        unsigned predicted_sum = (count * (count + 1))/2;
        unsigned diff = sum - predicted_sum;
        cout << diff << endl;
    } // while getline
}

