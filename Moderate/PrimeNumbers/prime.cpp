/* PRIME NUMBERS - CodeEval challenge

CHALLENGE DESCRIPTION:

Print out the prime numbers less than a given number N. For bonus points
your solution should run in N*(log(N)) time or better. You may assume
that N is always a positive integer.

INPUT SAMPLE:

Your program should accept as its first argument a path to a filename.
Each line in this file is one test case. Each test case will contain an
integer n < 4,294,967,295. E.g.

10
20
100

OUTPUT SAMPLE:

For each line of input, print out the prime numbers less than N, in
ascending order, comma delimited. (There should not be any spaces
between the comma and numbers) E.g.

2,3,5,7
2,3,5,7,11,13,17,19
2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97

*/

/*
	Use a "module" with some persistent state, namely the highest
	number for which primes <= that number have been computed (and
	stored in a vector).
	
	For each line and integer N:
	
	-- If a given N is greater than any seen before, compute the
	additional needed primes and add them to the vector.
	
	--Whether or not primes were added for this particular N,
	print out the primes less than N, comma separated.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

class sieve {
    static unsigned pmax;
    static vector<unsigned> pvec;
public:
    void print_primes_less_than( unsigned n );
    void compute_more_primes (unsigned n );
} primes;

unsigned sieve::pmax = 1;

vector<unsigned> sieve::pvec;

void sieve::compute_more_primes( unsigned n ) {
    // sieve::pvec contains all the primes up to and including n
    // (though n need not be a prime).
    // We have to find and save all the primes from pmax+1 through n
    for (unsigned i = pmax + 1; i < n; i++)
    {
        for (auto it = pvec.begin();
            it != pvec.end();
            ++it)
        {
            if (i % *it == 0)
                // nonprime
                goto next_one; // politically incorrect, but clear
        }
        pvec.push_back(i); // i is prime - save it
next_one:
        pmax = i;
    }
}

void sieve::print_primes_less_than( unsigned n )
{
    if (n > pmax) {
        compute_more_primes(n);
    }
    bool first = true;
    for (auto it = pvec.begin();
            it != pvec.end() && *it < n; ++it) {
        if (first)
            first = false;
        else
            cout << ',';	
        cout << *it;
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    if ( argc != 2 ) {
        cout <<"usage: "<< argv[0] <<" <filename>\n";
    }
    else {
        ifstream the_file ( argv[1] );
        if ( !the_file.is_open() )
            cout<<"Could not open file\n";
        else {
            while (true) {
                unsigned x;
                the_file >> x;
                if(the_file.eof())
                    break;
                primes.print_primes_less_than(x);
            }
        }
    }
}

// EOF
