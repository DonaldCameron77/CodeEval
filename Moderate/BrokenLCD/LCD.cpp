// BROKEN LCD - CodeEval Moderate challenge
// 
// CHALLENGE DESCRIPTION:
// 
// You have a 12-digit LCD, each digit consists of 8 segments: 7 segments
// to display numbers and one segment to display a decimal mark:
// 
//     <Graphic Omitted>
// 
// The number in each digit is displayed by turning segments on or off. It
// can be represented as a binary 8-bit number, each bit of which is a
// segment, ordered in the following binary representation:
// 
// Graphic not reproducible in text file.  But the LCD postions and
// the numbers assigned to each segment are as follows:
// 
//     111
//    6   2
//    6   2
//    6   2
//     777
//    5   3
//    5   3
//    5   3
//     444  8
// 
// Where 8 is the associated decimal.  I AM ASSUMING THE DECIMAL POINT
// MUST BE PRINTED ALONG WITH THE PRECEDING DIGIT - NOT BY ITSELF!
// 
// For example, number ‘4.’ (with the decimal mark turned on) corresponds
// to the following binary representation:
// 
//     <Graphic Omitted>
// 
// Some segments of the display are damaged and are always turned off. Your
// task is to determine whether a given number can be displayed on the
// damaged LCD. You can start displaying the number with the arbitrary
// digit of the LCD.
// 
// INPUT SAMPLE:
// 
// The first argument is a filename. Each line of the file contains binary
// 8-bit numbers, which represents the state of the segments, starting from
// the most left digit, and the number that you must show on the display.
// The binary numbers are separated by spaces, the number to display is
// separated by a semicolon.
// 
// For example:
// 
// 10111010 01101111 11101001 11101110 11111111 11111110 11111111 
// 01100101 10111111 11110100 10000111 01101011;6.9916
// 10100011 10111101 10111111 01100111 10001111 11000010 01110001 
// 11110011 01111111 11111110 11111111 11100111;7430.
// 10110101 01110111 11011111 11111110 11111111 11111010 11111111 
// 11111111 11111101 01110110 11111011 11111111;92.2720118
// 11111100 01111001 11110111 11110110 11111011 11111111 11111111 
// 11111110 10110110 11111101 11111111 11110110;570.02572
// 11001111 11100111 11110111 11111111 11100101 11111110 01111111 
// 11111111 11111000 11111111 11111111 10111111;7.3772427096
// 
// Every binary number represents the state of the segments in one digit. 1
// means that a segment is working and can be turned on or off, 0 means
// that a segment is damaged and is always turned off.
// 
// OUTPUT SAMPLE:
// 
// Print to stdout 1 for each test case if the number can be displayed on a
// given LCD, or 0 – if the number cannot be displayed. Print out one
// number in a line.
// 
// For example:
// 
// 1
// 1
// 0
// 1
// 0
// 
// CONSTRAINTS:
// 
// The number of test cases is 100.
// The damaged segments are always turned off.
// The number can be displayed starting from any digit.
// Every number has a decimal mark (if it is an integer, a decimal mark is
// placed after the last digit).

// Read and echo lines from filename given as first command-line argument.

/* * * * * * Algorithm * * * * * * * * * * * * * * * * * * * * * * * * 

Read in the actual digits into actual_digits[0..11]. Must convert the
binary to unsigned char.  Retain the given bit 0 (the decimal pt bit).

Suppose I read a 6 (with no decimal following).  digit_codes[6] is 0xBE.
Do I have any of the 12 LEDs that have at least those segments
available?  How do I test? 

I walk down the array of actual digits.  For each, I mask off the
cur_actual_digits with cur_input_digit, so that all unneeded digits
in the actual are zeroed.  Then I xor cur_input_digit with masked_actual
and the result should be zero for a match.  If no match, go on to the
next actual digit.  If there is a match, then if cur_input_digit
included a decimal not yet satisfied, or if cur_input_digit is rightmost
or by itself, then bit zero (decimal point) must be on in the actual.

ASSUMPTIONS:

1. The number to be displayed will not have a leading decimal point,
i.e, you won't see .1234
    
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <iostream>
#include <fstream>

#include <string>
#include <vector>

#include <cassert>

using namespace std;

// Minimum segments working to represent a digit.  These are numbered from
// the left, i.e., the digit 1 requires segments 2 and 3, which means
// that bits 5 and 6 must be on, i.e., 0110 0000 is the minimum (0x60).
static unsigned char digit_codes[] =
    { 0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6 };

struct Number_to_display {
    vector<unsigned> digits;
    int decimal_pos;
    Number_to_display() : decimal_pos(-1) {}
    // DEBUG
    void print_number();
    // DEBUG
};

// debug
void Number_to_display::print_number() {
    for (unsigned i = 0; i < digits.size(); ++i) {
        cout << digits[i];
        if (decimal_pos == int(i)) {
            cout << '.';
        }
    }
    cout << endl;
}
// debug

void parse_number(const string & number_string, Number_to_display & the_number)
{
    // assuming we can't have a leading decimal point in number_string
    the_number.digits.clear(); // can't hurt
    for (unsigned i = 0; i < number_string.length(); ++i) {
        if (number_string[i] == '.') {
            the_number.decimal_pos = int(i - 1);
        }
        else {
            the_number.digits.push_back( unsigned(number_string[i] - '0') );
        }
    }
}

const unsigned no_of_LCDs = 12; // from the problem description
typedef unsigned char LCD_status_arr[no_of_LCDs];

unsigned char binary_string_to_unsigned_char(const string & LCD_string) {
    assert(LCD_string.length() == 8);
    unsigned LCD_status = 0;
    for (unsigned i = 0; i < 8; ++i) {
        LCD_status = LCD_status * 2 + (LCD_string[i] - '0');
    }
    return LCD_status;
}

void parse_LCDs(const string & LCD_string, LCD_status_arr LCD_status)
{
    unsigned startpos = 0;
    for (unsigned i = 0; i < no_of_LCDs; ++i) {
        string next_LCD_string =
                LCD_string.substr(startpos, 8);
        startpos += 9; // skip over 8 char for binary byte, + trailing blank
        cout << next_LCD_string << endl;
        LCD_status[i] = binary_string_to_unsigned_char(next_LCD_string);
    }
}

bool can_display( const Number_to_display & the_number,
                  const LCD_status_arr & LCD_status) {
    // how will this work?
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    ifstream ifs(argv[1]);
    string line;

    while (getline(ifs, line)) {
        cout << line << endl;
        unsigned semi_pos = line.find(';');
        string number_string = line.substr(semi_pos + 1); // number to display
        cout << number_string << endl;
        Number_to_display the_number;
        parse_number(number_string, the_number);
        // DEBUG
        the_number.print_number();
        // DEBUG
        // line[semi_pos] = ' '; // facilitate parse
        LCD_status_arr LCD_status;
        parse_LCDs(line, LCD_status);
        cout << (can_display(the_number, LCD_status) ? 1 : 0 << endl; 
    } // while getline
}

// EOF
