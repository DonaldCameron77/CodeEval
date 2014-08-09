/* 
DECODE NUMBERS - CodeEval Moderate challenge
CHALLENGE DESCRIPTION:

You are given an encoded message containing only numbers. You are also provided with the following mapping:

A : 1
B : 2
C : 3
...
Z : 26

Given an encoded message, count the number of ways it can be decoded.

INPUT SAMPLE:

Your program should accept as its first argument a path to a filename. Each line in this file is a test-case and contains an encoded message of numbers. E.g.

12
123

You may assume that the test cases contain only numbers.

OUTPUT SAMPLE:

Print out the different number of ways it can be decoded. E.g.

2
3

NOTE: 12 could be decoded as AB(1 2) or L(12). Hence the number of ways to decode 12 is 2.
*/

#include <stdio.h>

const int l_min = 1; // may not need this
const int l_max = 26;

unsigned decode_helper(char * line, unsigned index) {
    // The idea is that the count returned is incremented
    // whenever a branch is created by finding a two-digit code.
    // Otherwise a "straight line" of single digits is assumed,
    // and the single path accounted for that is added in
    // the caller decode_path_count.

    // Note the paramerter 'line' is null-terminated
    if (line[index] == '\n') return 0;
    
    unsigned count = decode_helper(line, index + 1);

    if ((line[index + 1] != '\n') &&
        (line[index] == '1' ||
        (line[index] == '2' && line[index + 1] <= '6') ) )
    {
        count = count + 1; // accounting for the branch
        count = count + decode_helper(line, index + 2);
    }
    return count;
}

unsigned decode_path_count(char * line)
{
    unsigned count = decode_helper(line, 0 /* index into line */);
    return count + 1;
}

int main( int argc, char * argv[] )
{
    if (argc != 2) {
        printf("Usage: %s <text file>\n", argv[0]);
        return 1;
    }

    FILE * f;
    f = fopen(argv[1], "r");
    char line[1024];

    while (fgets(line, 1024, f)) {
        unsigned count = decode_path_count(line);
        printf("%d\n",  count);
    }

    return 0;
}

// EOF
