/*
ROMAN AND ARABIC - CodeEval Moderate challenge

CHALLENGE DESCRIPTION:

This question involves calculating the value of "aromatic" numbers which
are a combination of Arabic digits and Roman numerals. 

An aromatic number is of the form A1R1A2R2 ... AnRn , where each Ai is
an Arabic digit, and each Ri is a Roman numeral. Each pair AiRi
contributes a value described below, and by adding or subtracting these
values together we get the value of the entire aromatic number. 

An Arabic digit A can be 0, 1, 2, 3, 4, 5, 6, 7, 8 or 9. 

A Roman numeral R is one of the seven letters I, V, X, L, C, D, or M.
Each Roman numeral has a base value: 1, 5, 10, 50, 100, 500, 1000,
respectively. 

The value of a pair AR is A times the base value of R. Normally, you add
up the values of the pairs to get the overall value. However, wherever
there are consecutive symbols ARA`R` with R` having a strictly bigger
base value than R, the value of pair AR must be [subtracted] from the
total, instead of being added. 

For example, the number 3M1D2C has the value 3 × 1000 + 1 × 500 + 2 ×
100 = 3700 and 3X2I4X has the value 3 × 10 - 2 × 1 + 4 × 10 = 68 . Write
a program that computes the values of aromatic numbers. 

INPUT SAMPLE:

The input is a valid aromatic number consisting of between 2 and 20
symbols. Your program should accept as its first argument a path to a
filename. E.g.:

3M1D2C
2I3I2X9V1X

OUTPUT SAMPLE:

The output is the decimal value of the given aromatic number.

3700
-16

*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct aromatic {
    int total;
    int rval;
    aromatic(int t, int r) : total(t), rval(r) {}
};

// could hash this instead

int roman_map(char letter) {
    switch (letter) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: {
            cout << "ERROR in roman_map" << "\n";
            return 0;
        }
    } // case
}

int get_aromatic_number(const vector<aromatic> & v) {
    int answer = 0;
    int last_roman_val = 10000; // ensure we don't try to apply the
                                // "subtraction rule" on 1st ieration
    int last_val = 0; // shut up about uninit var compiler
    for (auto it=v.cbegin(); it != v.cend(); ++it)
    {
        int cur_val = it->total;
        int cur_roman_val = it->rval;
        if (cur_roman_val > last_roman_val) {
            // should have subtracted, not added, last time
            answer -= 2 * last_val;
        }
        answer += cur_val;
        last_roman_val = cur_roman_val;
        last_val = cur_val;
    }
    return answer;
}

int main(int argc, char * argv[])
{

    if (argc != 2) {
        cout << "usage: " << argv[0] << "<filename>\n";
        return 1;
    }

    ifstream ifs(argv[1]);
    string line;

    while (getline(ifs, line))
    {
        istringstream iss(line);
        int num;
        vector<aromatic> v;
        while (iss >> num) {
            char roman;
            iss >> roman;
            // cout << num << ' ' << roman << ";";
            int roman_value = roman_map(roman);
            aromatic a(num * roman_value, roman_value);
            v.push_back(a);

        }
        int answer = get_aromatic_number(v);
        cout << answer << "\n";
    } // while getline
}
