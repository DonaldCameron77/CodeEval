// Print the sum of the first 1000 primes

// Somewhat brute force, but omits all even numbers > 2, and 
// for a given number k, avoids checking divisors greater than
// sqrt(k).

// Would a sieve approach be faster?  Sieves are awkward when (as here)
// you don't know how many candidates you have to check.  We could
// hard code the highest number to check (since this is easily found),
// but a more general solution for the first n primes for any n is
// to start with a guess, and extend the sieve if that guess turns
// out to be too low.  And ... you probably don't want to use
// STL vector for the basic data structure.  You need to save the
// primes, so a traditional C-like array of bool would work, where
// the index indicates the prime (a[i] == true implies i is prime).

// Update July 2014.  I see I DID use std::vector.  And I checked for
// primality using the mod operator.  Getting the first n primes without
// doing extra work is ... a bit of a challenge, but the approach discussed
// above where you use a sieve and are able to extend it when you see you
// don't have enough primes yet ... that is the most promising way, I think.
//
// I did a little Ruby 'first 10 primes' program which guesses at the needed
// sieve size and runs the sieve algorithm until it has enough primes, but
// it has no facility to extend the sieve if needed.

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool is_prime( int cand, vector<int> & primes)
{
	int limit = sqrt(cand); // no need to search beyond this
	// loop on the divisors in the primes array
	for(vector<int>::iterator p = primes.begin(); p != primes.end(); ++p) {
		if (*p > limit) return true;
		if (cand % *p == 0) return false;
	}
	// should never reach here
	cout << "is_prime() error 1" << endl;
}

int sum_of_primes( int n ) {
	// start with 2 as the first prime
	int ctr = 1;
	int sum = 2;

	vector<int> primes;
	primes.push_back(2);

	// don't consider even numbers as candidates
	for (int cand = 3; ctr < n; cand += 2) {
		// int limit = sqrt(cand} + 1 // do we need the + 1 here? Ceiling of sqrt?
		// iterate on primes
		if (is_prime(cand, primes)) {
			sum += cand;
			ctr++;
			primes.push_back(cand);
		}	
	}
	return sum;
}

int main()
{
	const int n = 1000;
	int ans = sum_of_primes(n);
	cout << ans << endl;
}

