/*
ROBOT MOVEMENTS - CodeEval Hard challenge
CHALLENGE DESCRIPTION:

A robot is located at the top-left corner of a 4x4 grid. The robot can
move either up, down, left, or right, but can not visit the same spot
twice. The robot is trying to reach the bottom-right corner of the grid.

INPUT SAMPLE:

There is no input for this program.

OUTPUT SAMPLE:

Print out the unique number of ways the robot can reach its destination.
(The number should be printed as an integer whole number eg. if the
answer is 10 (its not !!), print out 10, not 10.0 or 10.00 etc)

*/

#include <iostream>
#include <vector>

using namespace std;

unsigned path_count = 0;

const int gridsize = 4; // 4x4 grid;

vector<vector<bool> > grid;

void generate_paths( int row, int col )
{
    if (row == gridsize - 1 && col == gridsize - 1) {
        // BINGO! reached goal ... & this is the base case
        ++ path_count;
        return;
    }
    
    // Has move taken us off the grid?
    if ( row < 0 || row == gridsize || col < 0 || col == gridsize)
        return;
    
    if (grid[row][col])	// current cell has been visited on current
        return;			// attempt to forge path
            
    grid[row][col] = true; // mark current as visited

    generate_paths(row - 1, col);
    generate_paths(row + 1, col);
    generate_paths(row, col - 1);
    generate_paths(row, col + 1);

    grid[row][col] = false; // unmark current
}

int main()
{
    grid.resize(gridsize);
    for (size_t i = 0; i < gridsize; i++)
        grid[i].resize(gridsize, false);
        
    generate_paths(0, 0);
    
    cout << path_count << endl;
}

