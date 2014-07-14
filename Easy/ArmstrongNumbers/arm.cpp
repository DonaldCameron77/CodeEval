/*
ARMSTRONG NUMBERS
CHALLENGE DESCRIPTION:

An Armstrong number is an n-digit number that is equal to the sum of the
n'th powers of its digits. Determine if the input numbers are Armstrong
numbers.

INPUT SAMPLE:

Your program should accept as its first argument a path to a filename.
Each line in this file has a positive integer. E.g.

6
153
351

OUTPUT SAMPLE:

Print out True/False if the number is an Armstrong number or not. E.g.

True
True
False

*/

#include <iostream>
#include <fstream>
#include <stack>
#include <cmath>

using namespace std;

bool is_armstrong_num( unsigned x ) {
    stack<unsigned> digits;
    unsigned ctr = 0;
    unsigned i = x;

    while (i) {
	unsigned digit = i % 10;
	digits.push(digit);
	i /= 10;
	ctr++;
    }

    // now x is untouched, ctr is the number of digits,
    // and digits contains the individual digits in the range 0..9
    // with the most significant at top of stack

    unsigned sum = 0;
    while (! digits.empty() ) {
	unsigned digit = digits.top();
	digits.pop();	
	sum = sum + (unsigned) pow( (float) digit, ctr );
    }

    return (sum == x) ? true : false;
}

int main ( int argc, char *argv[] )
{
    if ( argc != 2 ) {
	cout <<"usage: "<< argv[0] <<" <filename>\n";
    }
    else {
	// Assume argv[1] is a filename to open
	ifstream the_file ( argv[1] );
	// Check to see if file opening succeeded
	if ( !the_file.is_open() )
	    cout<<"Could not open file\n";
	else {
	    while (true) {
		unsigned x;
		the_file >> x;
		if( the_file.eof() ) break;
		if (is_armstrong_num(x))
		    cout << "True";
		else
		    cout << "False";
		cout << endl;
	    }
	}
    }
}
// EOF

