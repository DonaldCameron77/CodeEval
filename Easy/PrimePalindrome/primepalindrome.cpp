/*
PRIME PALINDROME - CodeEval Easy challenge
CHALLENGE DESCRIPTION:

Write a program to determine the biggest prime palindrome under 1000.

INPUT SAMPLE:

There is no input for this program.

OUTPUT SAMPLE:

Your program should print the largest palindrome on stdout, i.e.

929

*/

// TODO - convert to use STL more liberally;
// e.g. use Vector for the primes array

#include <iostream>

using namespace std;

// check if a number under 1k is prime.  We could do this faster
// in general by precomputing the primes, but we know we're working
// down from 1000 trying to find a palindromic one, so we probably
// aren't going to look at very many numbers.
bool is_prime_under_1k( int n ) {
    static int primes[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    for (unsigned i = 0; i < sizeof(primes)/sizeof(int); i++) {
  	if (n % primes[i] == 0) {
	    return false;
  	}
    }
    return true;
}

// check if positive integer is palindromic
bool is_palindrome( int x ) {
    int rev = 0;
    int i = x;
    do {
	int r = i % 10;
	rev = rev * 10 + r;
	i = i / 10; 
    } while (i > 0);
    return x == rev;
}

// find what the name implies
int largest_prime_pal_under_1000() {
    // even numbers excluded and we know 999 is nonprime,
    // so start with the next smaller palindrome which is 989
    for (int candidate = 989; candidate > 2; candidate -= 2) {
	if (is_palindrome( candidate ) && is_prime_under_1k( candidate )) {
	    return candidate;
	}
    }
    return -1; // error exit
}

int main() {
    int ans = largest_prime_pal_under_1000();
    if (ans == -1) {
	cout << "fail" << endl;
    }
    else {
	cout << ans << endl;
    }
}
// EOF

