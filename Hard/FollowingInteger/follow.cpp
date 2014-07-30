/* 
   CodeEval Moderate challenge
   
You are writing out a list of numbers.Your list contains all numbers
with exactly Di digits in its decimal representation which are equal to
i, for each i between 1 and 9, inclusive. You are writing them out in
ascending order. For example, you might be writing every number with two
'1's and one '5'. Your list would begin 115, 151, 511, 1015, 1051. Given
N, the last number you wrote, compute what the next number in the list
will be. The number of 1s, 2s, ..., 9s is fixed but the number of 0s is
arbitrary.

INPUT SAMPLE:

Your program should accept as its first argument a path to a filename.
Each line in this file is one test case. Each test case will contain an
integer n < 10^6. E.g.

115
842
8000
OUTPUT SAMPLE:

For each line of input, generate a line of output which is the next
integer in the list. E.g.

151
2048
80000

Additional cases (more difficult):

3269
81637
874199
252256

*/

#include <iostream>
#include <fstream>

// using namespace std;

// I think these routines are cheaper than doing I/O on individual digits.
// However, that means the digits are in a conventional array in reverse
// order.

void dissect_int( int a[], int x, int & d) {
    d = 0; // Slightly cute.  d is array index, finishes as actual len
    while (x) {
	a[d++] = x % 10;
	x /= 10;
    }
}

int assemble_int( int a[], int len) {
    int result = 0;
    for (int i = len - 1; i >= 0; i--) {
	result = result * 10 + a[i];
    }
    return result;
}

void do_sort( int a[], int start, int end ) {
    // arrange digits in a[start] .. a[end] in descending order.
    // end - start is small so a simple O(n^2) sort is fine
    // if (start < end) cout << "oops - do_sort unimplemented" << endl;
    bool changed;
    do {
	changed = false;
	for (int i = end; i > start; i--) {
	    if (a[i] > a[i-1]) {
		int temp = a[i];
		a[i] = a[i-1];
		a[i-1] = temp;
		changed = true;
	    }
	}
    } while (changed);
}

void do_nextint( int x ) {
    using namespace std;
    const unsigned asize = 16; // should be plenty: input ints limited to 999,999
    int a[asize];
    int len;
    
    dissect_int(a, x, len);

    /*  Note that a[0] is the least significant digit.  References in this
	explanation to "left" and "right" refer to this original, natural ordering,
	not the reverse one in the array a.

	First, scan starting at a[0] and find the first s such that a[s-1] is greater
	than a[s]. If such an s exists, scan starting at a[0] and find the first
	i such that a[i] is greater than a[s].  Swap a[i] and a[s]. The digits
	a[0] .. a[s-1] remain in ascending order.  We could simply reverse them,
	but I use a simple sort routine instead.

	If the first scan does not find such an s, then all the digits are in ascending
	order. We must extend the array by one cell, put a[0] in that cell and zero
	in a[0], and reverse (i.e., sort) a[0] .. a[newlength-2].
    */

    int s = 1;
    while (s < len && a[s-1] <= a[s]) s++;

    if (s < len) {
	// Simple swap, keeping the same number of digits.
	// Swap with rightmost digit < a[s]
	int i = 0;
	while (i < s && a[i] <= a[s]) i++;
	// swap a[i] with a[s]
	int temp = a[i];
	a[i] = a[s];
	a[s] = temp;
	do_sort(a, 0, s-1);
	}
    else {
	// digits are ascending.  Note number could be, e.g., 8000.
	// Find leftmost nonzero digit,  Note we are guaranteed there is one.
	int i = 0;
	while (i < len && a[i] == 0) i++;
	a[len++] = a[i];
	a[i] = 0;
	do_sort(a, 0, len - 2);
    }

    int y = assemble_int(a, len);
    cout << y << endl;
}

int main ( int argc, char *argv[] ) {
    using namespace std;
    if ( argc != 2 ) // argc should be 2 for correct execution
	// Print argv[0] assuming it is the program name
	cout <<"usage: "<< argv[0] <<" <filename>\n";
    else {
	// Assume argv[1] is a filename to open
	ifstream the_file ( argv[1] );
	// Check to see if file opening succeeded
	if ( !the_file.is_open() )
	    cout<<"Could not open file\n";
	else {
	    int x;
	    while (the_file >> x) {
		do_nextint(x);
	    }
	}
    }
}
// EOF

