/*
    SUDOKU - CodeEval Moderate challenge

    CHALLENGE DESCRIPTION:

    Sudoku is a number-based logic puzzle. It typically comprises of a 9*9
    grid with digits so that each column, each row and each of the nine 3*3
    sub-grids that compose the grid contains all the digits from 1 to 9. For
    this challenge, you will be given an N*N grid populated with numbers
    from 1 through N and you have to determine if it is a valid sudoku
    solution. You may assume that N will be either 4 or 9. The grid can be
    divided into square regions of equal size, where the size of a region is
    equal to the square root of a side of the entire grid. Thus for a 9*9
    grid there would be 9 regions of size 3*3 each.

    INPUT SAMPLE:

    Your program should accept as its first argument a path to a filename.
    Each line in this file contains the value of N, a semicolon and the
    sqaure matrix of integers in row major form, comma delimited. E.g.

    4;1,4,2,3,2,3,1,4,4,2,3,1,3,1,4,2
    4;2,1,3,2,3,2,1,4,1,4,2,3,2,3,4,1

    OUTPUT SAMPLE:

    Print out True/False if the grid is a valid sudoku layout. E.g.

    True
    False
*/

// Read lines from filename given as first command-line argument.
// Parse whitespace-separated integers from line into vector n.

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

// Values have been entered into a sudoku board of size dim x dim in row major
// order, and the next value to be entered will be nextval at board[row,col].
// Check that nextval does not conflict with values already entered.
bool insert_if_valid( vector <vector<int> > & board, unsigned dim,
	 unsigned row, unsigned col, const int nextval)
{
    // check against row
    for (unsigned c = 0; c < col; c++) {
	if (nextval == board[row][c]) {
	    return false;
	}
    }
    
    // check against column
    for (unsigned r = 0; r < row; r++) {
	if (nextval == board[r][col]) {
	    return false;
	}
    }
    
    // check against block
    
    /*  We are filling up a row before moving on to the next. For a plain
	NxN square matrix, inserting at row, col, the for loop on rows
	is 
		for (r = 0; r <= row; r++)
			
	and it's left to the column loop to ensure we don't look to the
	right of the col-th column in the final row:
			
		for (c = 0; (r < row && c < N) || (r == row && c < col); c++)
			
	(where we should verify that r == row is redundant).
			
	However, we are dealing with sub-regions (blocks in Sudoku parlance).
	Hence the inital values of the loop control variables are
	 
		(<row (or col) / blocksize) * blocksize
	
	thanks to the properties of integer division.
	
	The condition for the rows is still r <= row.
	
	The condition for the columns is almost the same, but we have to replace
	c < N in the above with c <= <the highest column number in the block>,
	which is 
	
		(col/blocksize) * blocksize + blocksize - 1
    
    */
    
    unsigned blocksize = (unsigned)sqrt(dim);
	    
    for (unsigned r = (row / blocksize) * blocksize; r <= row; r++)
    {
	for (	unsigned c = (col / blocksize) * blocksize;
		(r < row && c < (col/blocksize) * blocksize + blocksize - 1)
			 || (r == row && c < col);
		c++) {
	    if (nextval == board[r][c])
		return false;
	}
    }
    
    // if we had started with an empty board, we would 
    // have to add using board[row].push_back(nextval).
    // Instead, we create a 9x9 board, and only use part
    // of it if dim is 4.
     
    board[row][col] = nextval;
    return true;
}

// Inps is a stream of comma-separated integers in the range 1..dim
// representing a completed sudoku board of size dim x dim. 
void do_sudoku(const unsigned dim, istringstream & inps)
{
    vector <vector <int> > board (9, vector<int>(9, 0));
    
    for (unsigned row = 0; row < dim; row++ ) {
	for (unsigned col = 0; col < dim; col++){
	    int nextval;
	    inps >> nextval;
	    if (nextval < 1 || nextval > (int)dim) {
		cerr << "Unexpected cell value - aborting" << nextval << endl;
		exit(3);
	    }
	    if (!insert_if_valid(board, dim, row, col, nextval)) {
		cout << "False" << endl;
		return;
	    }

	} // for row
    } // for col
    
    // normal loop exit -> no conflicts
    cout << "True" << endl;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
	cerr <<"usage: "<< argv[0] <<" <filename>\n";
	exit(1);
    }

    ifstream ifs(argv[1]);
    string line;

    while (getline(ifs, line)) {
	if (line.size() == 0) {
	    continue;
	}

	for (unsigned i = 0; i < line.size(); i++) {
	    if (line[i] == ',') {
		line[i] = ' '; // reaplce comma separators
	    }
	}

	istringstream inps(line);
	unsigned dim;
	inps >> dim;

	if (!(dim == 4 || dim == 9)) {
	    cerr << "Bad dimension specification - aborting" << endl;
	    exit(1);
	}

	char ctemp;
	inps >> ctemp;

	if (ctemp != ';') {
	    cerr << "Bad character - expected semicolon - aborting" << endl;
	    exit(2);
	}
					   
	do_sudoku(dim, inps); 

    } // while getline

    exit(0);
}
