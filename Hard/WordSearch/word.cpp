/*
WORD SEARCH - CodeEval Hard challenge
CHALLENGE DESCRIPTION:

Given a 2D board and a word, find if the word exists in the grid. The
word can be constructed from letters of sequentially adjacent cell,
where adjacent cells are those horizontally or vertically neighboring.
The same letter cell may not be used more than once.

The board to be used may be hard coded as:

[
[ABCE],
[SFCS],
[ADEE]
]

INPUT SAMPLE:

Your program should accept as its first argument a path to a filename.
Each line in this file contains a word. E.g.

ASADB
ABCCED
ABCF

OUTPUT SAMPLE:

Print out True if the word exists in the board, False otherwise. E.g.

False
True
False
*/

#include <iostream>
#include <fstream>

using namespace std;

const int nrows = 3;
const int ncols = 4;

struct Cell {
    char letter;
    bool used;  // true --> already incorporated in current search,
                // so don't re-use;
};

typedef Cell Row[ncols];

Row Grid[] =
    {
        { { 'A', false }, { 'B', false }, { 'C', false }, { 'E', false } },
        { { 'S', false }, { 'F', false }, { 'C', false }, { 'S', false } }, 
        { { 'A', false }, { 'D', false }, { 'E', false }, { 'E', false } } 
    };


/*//////////////////////////////////////////////////////////////////////////
    Is starting from a Cell where you have not matched anything
    different than 


*///////////////////////////////////////////////////////////////////////////

bool off_grid(int row, int col) {
    return row < 0 || row == nrows || col < 0 || col == ncols;
}

bool word_search(
    string & word, unsigned word_index, int row, int col )
{
    if ( off_grid(row, col) ||
         Grid[row][col].used ||
         Grid[row][col].letter != word[word_index])
        return false;

    if (word_index + 1 == word.size()) return true;

    Grid[row][col].used = true;
    bool found =
        word_search(word, word_index+1, row - 1, col) ||
        word_search(word, word_index+1, row + 1, col) ||
        word_search(word, word_index+1, row, col - 1) ||
        word_search(word, word_index+1, row, col + 1);
    Grid[row][col].used = false;
    return found;
}

// need this routine to start from all grid cells (until success)
bool word_search( string & word ) {
    for (int r = 0; r < nrows; ++r) {
        for (int c = 0; c < ncols; ++c) {
            if (word_search(word, 0, r, c )) {
                return true;
            }
        }
    }
    return false;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "usage: " << argv[0] << "<filename>\n";
        return 1;
    }

#ifdef DEBUG
    for (int r = 0; r < nrows; ++r) {
        for (int c = 0; c < ncols; ++c) {
            cout << Grid[r][c].letter << ' ';
        }
        cout << "\n";
    }
#endif

    ifstream ifs(argv[1]);
    string line;

    while (getline(ifs, line)) {
#ifdef DEBUG
        cout << "next word is: '" << line << "'\n";
#endif
        cout << (word_search(line) ? "True" : "False") << "\n";
    } // while getline
}
