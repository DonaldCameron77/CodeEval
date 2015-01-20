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
// 
// 10110001 11111000 11111110 11111111 11111111 11111111 11111111 11101101
// 11111111 01111111 11110010 10100111;84.525784
// 11111111 11110110 11101111 11110111 10111110 11110110 10111011 10100111
// 11111100 01100100 11111101 01011110;5.57
// 11000010 00001111 11111111 10111111 11101011 11110011 01111110 11011111
// 11111111 11111111 11111001 01101110;857.71284
// 11111111 01110111 10111011 11001101 11111011 11101010 11110100 01001101
// 11011111 11111010 10010110 10111111;66.92
// 11111011 10010001 11111011 11111101 10011111 10111110 01111100 11011101
// 10111001 11111110 11101111 11110110;188.87
// 
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
// 1
// 0
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

////////////////////////////////////////////////////////////////////////////////
//
//   Stuff having to do with the number to display
//   - comes after ';' in input line
//

struct Number_to_display {
    vector<unsigned char> digits;
    int decimal_pos;
    // decimal_pos == -1 implies no decimal point was seen in the input number
    Number_to_display() : decimal_pos(-1) {}
#ifdef DEBUG
    void print_number();
#endif // DEBUG
};

#ifdef DEBUG
void Number_to_display::print_number() {
    for (unsigned i = 0; i < digits.size(); ++i) {
        cout << digits[i];
        if (decimal_pos == int(i)) {
            cout << '.';
        }
    }
    cout << endl;
}
#endif // DEBUG

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

////////////////////////////////////////////////////////////////////////////////
//
//   Stuff having to do with the incoming LCD status info 
//

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

#ifdef DEBUG
bool can_display_digit(
                const unsigned digit_code_needed, const unsigned LCD_status );

// normal location further down in file - commented out during debug
static unsigned char digit_codes[] =
    { 0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6 };
    
void print_displayable_digits( unsigned char LCD_byte) {
    for (unsigned i = 0; i < 10; ++i) {
        if (can_display_digit( digit_codes[i], LCD_byte )) {
            cout << ' ' << i;
        }
    }
    // print decimal point if available in LCD_byte
    if (LCD_byte & 0x1) {
        cout << " .";
    }
}
#endif // DEBUG

void parse_LCDs(const string & LCD_string, LCD_status_arr LCD_status)
{
    unsigned startpos = 0;
    for (unsigned i = 0; i < no_of_LCDs; ++i) {
        string next_LCD_string =
                LCD_string.substr(startpos, 8);
        startpos += 9; // skip over 8 char for binary byte, + trailing blank
        LCD_status[i] = binary_string_to_unsigned_char(next_LCD_string);
#ifdef DEBUG
        cout << i << ' ' << next_LCD_string;
        print_displayable_digits(LCD_status[i]);
        cout << endl;
#endif // DEBUG
    }
}

////////////////////////////////////////////////////////////////////////////////
//
//   Stuff concerning whether a number can be represented by the current state
//   the 12 LCDs
//

#ifndef DEBUG
// moved higher for debug purposes

// Minimum segments working to represent a digit.  These are numbered from
// the left, i.e., the digit 1 requires LCD segments 2 and 3, which means
// that bits 5 and 6 (0 based and counting from the left) must be on,
// i.e., 0110 0000 is the minimum (0x60).
static unsigned char digit_codes[] =
    { 0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6 };
#endif // DEBUG


bool can_display_digit(
                const unsigned digit_code_needed, const unsigned LCD_status ) {
    // check that all bits set in digit_needed are also set in LCD_status
    return (digit_code_needed & LCD_status) == digit_code_needed;
}

bool can_display( const Number_to_display & the_number,
                  const LCD_status_arr & LCD_status)
{
    unsigned no_digits_in_number = the_number.digits.size();
    
    // index in number array of decimal point
    int decimal_pos = the_number.decimal_pos;
    if (decimal_pos == -1) {
        decimal_pos = no_digits_in_number - 1;
    }
    
    for (unsigned cur_LCD_start = 0;
         cur_LCD_start <= no_of_LCDs - no_digits_in_number;
         ++cur_LCD_start)
    {
        // first check if the decimal point can be displayed
        if ((LCD_status[cur_LCD_start + decimal_pos] & 1) == 0) {
            continue;
        }
        for (unsigned cur_digit_index = 0;
             cur_digit_index < no_digits_in_number;
             ++cur_digit_index)
        {
            unsigned char cur_digit = the_number.digits[cur_digit_index];
            if (!can_display_digit( digit_codes[cur_digit],
                        LCD_status[cur_LCD_start + cur_digit_index] )) {
                goto break2;
            }
        }
        return true;
break2: ;
    }
    return false;
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
#ifdef DEBUG
        cout << line << endl;
#endif // DEBUG
        unsigned semi_pos = line.find(';');
        string number_string = line.substr(semi_pos + 1); // number to display
#ifdef DEBUG
        cout << number_string << endl;
#endif // DEBUG
        Number_to_display the_number;
        parse_number(number_string, the_number);
#ifdef DEBUG
        the_number.print_number();
#endif // DEBUG
        // line[semi_pos] = ' '; // facilitate parse
        LCD_status_arr LCD_status;
        parse_LCDs(line, LCD_status);
        cout << (can_display(the_number, LCD_status) ? 1 : 0) << endl; 
    } // while getline
}

// EOF

