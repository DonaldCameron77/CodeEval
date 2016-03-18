/*
    MERSENNE PRIME - CodeEval Easy challenge

    CHALLENGE DESCRIPTION:

    In January 2013, GIMPS contributors discovered the 48th known Mersenne
    prime number. For this, they received a $100,000 award. A newly
    announced $150,000 reward will be given to those who will discover the
    next largest known prime. Do not want to get it? We offer this challenge
    to you to get ready.

    INPUT SAMPLE:

    The first argument is a path to a file. Each line includes a test case
    with an integer.

    4
    308

    OUTPUT SAMPLE:

    Your task is to print all Mersenne numbers that are smaller than
    the number in a test case. Separate those numbers by commas.

    3
    3, 7, 31, 127

    CONSTRAINTS:

    The number in a test case can be from 4 to 3,000.
    The number of test cases is 20.
*/

/* Notes:
    1. Despite the title, the exercise concerns Mersenne numbers, not
    Merseen primes.
    2. Mersenne numbers have the form 2^p - 1.  Codeeval requires the
    additional contraint, in agreement with some but not all authors,
    that p be prime.
*/

#include <stdio.h>
#include <stdbool.h>

/*
    A Mersenne number has the form 2^p-1 where p is prime.
*/

// do whatever for next item .. in this case, print it
// in a list formatted as k1, k2, ... kn
static bool first;
void process_item(unsigned k) {
    if (!first) {
        printf(", ");
    }
    printf("%d", k);
    first = false;
}
void start_items() { first = true; }
void finish_items() { printf("\n"); }

/* is_prime(k) : Check a single unsigned int k for primality (limited to 32 bit signed int range.
 * See http://stackoverflow.com/questions/1801391/what-is-the-best-algorithm-for-checking-if-a-number-is-prime
 * 
 * Relies on primes > 2 & 3 having the form 6k - 1 and 6k + 1
 *
 * (see
 * http://www.quora.com/Is-every-prime-number-other-than-2-and-3-of-the-form-6k%C2%B11
 * for explanation).
 */

// Variant of the classic O(sqrt(N)) algorithm.
// Returns 1 (true) if k is prime
bool is_prime(unsigned k) {
    if (k == 2) return true; 
    if (k == 3) return true; 
    if (k % 2 == 0) return false;
    if (k % 3 == 0) return false;

    unsigned i = 5;
    unsigned w = 2;

    while (i * i <= k) {
        if (k % i == 0)
            return false;
        
        i += w;
        w = 6 - w;
    }

    return true;
}

// EOF

// generate Mersenne numbers up to but not including limit
// (which may not itself be a Mersenne number)
void mersenne(unsigned limit) {
    start_items();
    if (limit > 3) {
        for (unsigned p = 2; p <= 32; ++p) { // limiting ourselves to 32 bits
            if (is_prime(p)) {
                unsigned M = (1 << p) - 1;
                if (M >= limit) {
                    break;
                }
                process_item(M);
            }
        }
    }
    finish_items();
}

int main(int argc, const char * argv[]) {
    FILE *file = fopen(argv[1], "r");
    char line[1024];
    while (fgets(line, 1024, file)) {
        unsigned limit;
        sscanf(line, "%d", & limit);
        mersenne(limit);
    }
    return 0;
}

// EOF
