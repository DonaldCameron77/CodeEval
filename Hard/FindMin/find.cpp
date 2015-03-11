// FIND MIN - CodeEval Hard challenge
// CHALLENGE DESCRIPTION:
// 
// Credits: This problem appeared in the Facebook Hacker Cup 2013 Hackathon. 
// 
// After sending smileys, John decided to play with arrays. Did you know
// that hackers enjoy playing with arrays? John has a zero-based index
// array, m, which contains n non-negative integers. However, only the
// first k values of the array are known to him, and he wants to figure out
// the rest. 
// 
// John knows the following: for each index i, where k <= i < n, m is the
// minimum non-negative integer which is *not* contained in the previous
// *k* values of m. 
// 
// For example, if k = 3, n = 4 and the known values of m are [2, 3, 0], he
// can figure out that m[3] = 1. John is very busy making the world more
// open and connected, as such, he doesn't have time to figure out the rest
// of the array. It is your task to help him. Given the first k values of
// m, calculate the nth value of this array. (i.e. m[n - 1]).Because the
// values of n and k can be very large, we use a pseudo-random number
// generator to calculate the first k values of m. Given positive integers
// a, b, c and r, the known values of m can be calculated as follows:
// 
//     m[0] = a
//     m = (b * m[i - 1] + c) % r, 0 < i < k
//     
// INPUT SAMPLE:
// 
// Your program should accept as its first argument a path to a filename.
// Each line in this file contains 6 comma separated positive integers
// which are the values of n,k,a,b,c,r in order. E.g.
// 
// 78,51,3,5,5,51230
// 186,75,68,16,539,312
// 137,135,48,17,461,512
// 98,22,6,30,524,100
// 46,18,7,11,9,46
// 
// OUTPUT SAMPLE:
// 
// Print out the nth element of m for each test case e.g.
// 
// 26
// 34
// 1
// 6
// 12

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])
{
    ifstream ifs(argv[1]);
    string line;

    while (getline(ifs, line))
    {
        // debug
        // cout << line << endl;

        // ease the parse
        replace(line.begin(), line.end(), ',', ' ');

        istringstream line_stream(line);

        long n;  // size of array m
        long k;  // number of initially-known elements in m
        long a;  // a, b, c, and r used to generate 1st k elements
        long b;
        long c;
        long r;

        line_stream  >> n >> k >> a >> b >> c >> r;
        
        vector<unsigned> m(k);  // start with k elements only
        m[0] = a;
        for (unsigned x = 1; x < k; ++x) {
            m[x] = (b * m[x - 1] + c) % r;
        }

        for (unsigned y = k; y < n; ++y)
        {
            // n.b. in a range of the rightmost k elements of m,
            // we are expecting to find a minimum missing element,
            // thus we are trying k+1 elements, i.e.,  [0..k]

            for (unsigned val = 0; val <= k; ++val)
            {
                // if val is missing in m[y-k .. y-1] then m[y] := val
                if (find(m.end()-k, m.end(), val) == m.end())
                {
                    m.push_back(val);
                    break;
                }
            }
        }

        cout << m.back() << endl; 


        // split line into 6 integers
    } // while getline
}

// EOF
