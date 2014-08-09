
/* CodeEval Easy challenge - given integer, print Roman Numeral representation

CHALLENGE DESCRIPTION:

Many persons are familiar with the Roman numerals for relatively small
numbers. The symbols I (capital i), V, X, L, C, D, and M represent the
decimal values 1, 5, 10, 50, 100, 500 and 1000 respectively. To
represent other values, these symbols, and multiples where necessary,
are concatenated, with the smaller-valued symbols written further to the
right. For example, the number 3 is represented as III, and the value 73
is represented as LXXIII. The exceptions to this rule occur for numbers
having units values of 4 or 9, and for tens values of 40 or 90. For
these cases, the Roman numeral representations are IV (4), IX (9), XL
(40), and XC (90). So the Roman numeral representations for 24, 39, 44,
49, and 94 are XXIV, XXXIX, XLIV, XLIX, and XCIV, respectively. 

Write a program to convert a cardinal number to a Roman numeral.

INPUT SAMPLE:

Your program should accept as its first argument a path to a filename.
Input example is the following

159
296
3992

Input numbers are in range [1, 3999]

OUTPUT SAMPLE:

Print out Roman numerals.

CLIX
CCXCVI
MMMCMXCII
*/

#include <stdio.h>

// these could easily be local to main

#define NUM_TOKS 10

// Roman numeral notation did not require or use a zero.
char * rns [][NUM_TOKS] = {
    { "Error", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" },
    { "Error", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC" },
    { "Error", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM" },
    { "Error", "M", "MM", "MMM",
                 "Error", "Error", "Error", "error", "error", "error" } };
  
enum e_place { unassigned = -1, ones, tens, hundreds, thousands };

#define MAX_CHUNKS 4
struct { char * parts[MAX_CHUNKS];
     enum e_place place;
} answer;

char * romlist[MAX_CHUNKS];   

int main(int argc, char * argv[])
{
    if (argc != 2) {
        printf("Usage: %s <text file>\n", argv[0]);
        return 1;
    }

    FILE * f;
    f = fopen(argv[1], "r");
    char line[1024];
    while (fgets(line, 1024, f)) {
        int num;
        sscanf(line, "%d", &num);
        // printf("%d\n", num);
        
        answer.place = unassigned;
        int last_romchunk = -1;
        
        while (num > 0) {
            // assert i < NUM_PLACES);
            int digit = num %10;
            num /= 10;
            answer.place++;
            romlist[++last_romchunk] =
                    digit == 0 ? NULL : rns[answer.place][digit];
            
        }
        
        // now romlist[0 .. last_romchunk] contains the Roman numeral
        // in reverse order
        
        for (int i = last_romchunk; i >= 0; i--) {
            if (romlist[i] != NULL)
                printf("%s", romlist[i]);
        }
        printf("\n");
    }

return 0;
}
// EOF
