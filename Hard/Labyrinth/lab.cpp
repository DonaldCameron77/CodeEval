/*
THE LABYRINTH - CodeEval Hard challenge
CHALLENGE DESCRIPTION:

You are given a text with a pseudographical schema of a labyrinth. Walls
are marked with asterisk symbols (*). Your job is to write a program
that finds the shortest way from the upper entrance to the lower exit
and prints out the labyrinth schema containing a path marked with plus
symbols (+).

INPUT SAMPLE:

A text file with labyrinth schema.

************************* *************************
*                                   * *           *
* * *** *** ******************* ***** * * * * * ***
* * *   * *   *   * * *                 * * * *   *
***** * * *** * *** * * *** *** * ***** *** *******
*     * *   * *     *   * * *   *     * * *       *
*** ******* * ***** *** * * ******* * *** * *** * *
* *     *     *   *     *     *     * *       * * *
* * *********** * ********* * ******* * *** * *****
*     * *   * * *     *     * *   *   * *   *     *
* ***** * *** * ***** *** *** * * * ******* ***** *
* *     *   * * *       * * *   * * * *   *     * *
* * ***** *** *** *** *** * ***** *** *** ***** ***
*     *   * * *     * *       * *       * *     * *
* * ***** * * * *** * *** ***** *** ***** *** * * *
* * *           *   * *   *     *     *     * *   *
* ******* ******* * *** ******* *** * * ********* *
*   *       *     * *   *         * * * *     *   *
*** * * ***** * ***** ******* ******* * * * * * ***
*     *   *   *         *       * *   * * * * *   *
*** * *** * *** ***** ******* * * * *** *** * *** *
* * * * * * * *     * * *     *       *   * * * * *
* * *** * * * *** *** * * ********* ***** * * * * *
* * *   * * *     *   * *   *     *   *     * * * *
* * * *** ******* ***** * ******* *** * *** *** * *
* * *     *   *   *     * *     * * * *   *   * * *
* ***** * * * *** * ***** ***** * * * ***** * * * *
* *     * * * *     * *     *           * * *   * *
* ***** * *** * ***** *********** ******* * * * * *
*     * * * *             *   *     * * *   * * * *
* * * *** * *** * ***** ***** ******* * *** * * * *
* * *   * * *   *     * *             *     * * * *
* ***** * * *********** ******* *** * ******* * * *
* *     *   *   *     * *   *   * * *       * *   *
* * * ********* * ***** * *** *** *** * ***** * ***
* * *       *           *   * * *   * *   *   *   *
* ******* ***** ******* * *** * * *** *** * *******
*   *   *   *   *   *     *         * * * * * * * *
* ***** * *** ***** * ******* * ***** * *** * * * *
*     *           *     *     * * *   *   *     * *
*** *** ********************* *** *** *** *** * * *
*   *   *     *               * * *   *       *   *
*** *** * ***** * ******* *** * * *** * *** ***** *
*       *       *   *   * * *   *     *   * *   * *
*** ***** ***** *** *** *** ***** * * *** *** * * *
*       *   *   * * *       *   * * *   * *   *   *
*** *** * ***** * ***** *** *** *** *** ******* ***
*   *     *   *   *     * * * *     * * *     *   *
* ***** *** ***** ******* * * *** *** * *** ***** *
*   *                 *           *         *     *
************************* *************************

OUTPUT SAMPLE:

Print to stdout the labyrinth schema containing the shortest way out
marked with ‘+’ symbols:

*************************+*************************
*                        +++++++    * *           *
* * *** *** *******************+***** * * * * * ***
* * *   * *   *   * * *    +++++        * * * *   *
***** * * *** * *** * * ***+*** * ***** *** *******
*     * *   * *     *   * *+*   *     * * *       *
*** ******* * ***** *** * *+******* * *** * *** * *
* *     *     *   *     *  +  *     * *       * * *
* * *********** * *********+* ******* * *** * *****
*     * *   * * *     *  +++* *   *   * *   *     *
* ***** * *** * ***** ***+*** * * * ******* ***** *
* *     *   * * *       *+* *   * * * *   *     * *
* * ***** *** *** *** ***+* ***** *** *** ***** ***
*     *   * * *     * *  +    * *       * *     * *
* * ***** * * * *** * ***+***** *** ***** *** * * *
* * *           *   * *+++*     *     *     * *   *
* ******* ******* * ***+******* *** * * ********* *
*   *       *     * *+++*         * * * *     *   *
*** * * ***** * *****+******* ******* * * * * * ***
*     *   *   *+++++++  *       * *   * * * * *   *
*** * *** * ***+***** ******* * * * *** *** * *** *
* * * * * * * *+++  * * *     *       *   * * * * *
* * *** * * * ***+*** * * ********* ***** * * * * *
* * *   * * *    +*   * *   *     *   *     * * * *
* * * *** *******+***** * ******* *** * *** *** * *
* * *     *   *  +*     * *     * * * *   *   * * *
* ***** * * * ***+* ***** ***** * * * ***** * * * *
* *     * * * *+++  * *     *           * * *   * *
* ***** * *** *+***** *********** ******* * * * * *
*     * * * *  +++++++++  *   *     * * *   * * * *
* * * *** * *** * *****+***** ******* * *** * * * *
* * *   * * *   *     *+*      +++++++*     * * * *
* ***** * * ***********+*******+*** *+******* * * *
* *     *   *   *     *+*   *+++* * *+      * *   *
* * * ********* * *****+* ***+*** ***+* ***** * ***
* * *       *  +++++++++*   *+* *   *+*   *   *   *
* ******* *****+******* * ***+* * ***+*** * *******
*   *   *   *+++*   *     *  +      *+* * * * * * *
* ***** * ***+***** * *******+* *****+* *** * * * *
*     *+++++++    *     *    +* * *  +*   *     * *
*** ***+*********************+*** ***+*** *** * * *
*   *  +*     *+++++++++++++++* * *  +*       *   *
*** ***+* *****+* ******* *** * * ***+* *** ***** *
*  +++++*+++++++*   *   * * *   *  +++*   * *   * *
***+*****+***** *** *** *** ***** *+* *** *** * * *
*  +++++*+  *   * * *       *   * *+*   * *   *   *
*** ***+*+***** * ***** *** *** ***+*** ******* ***
*   *  +++*   *   *     * * * *  +++* * *     *   *
* ***** *** ***** ******* * * ***+*** * *** ***** *
*   *                 *  +++++++++*         *     *
*************************+*************************

CONSTRAINTS:

The size of a labyrinth is up to 101×101 cells. There can be more than
one way to pass the labyrinth, but the shortest way is always
unambiguous and never has branches.
*/

/* Theory of Operation
     Each instance of the recursion (in find_helper, I think it will be) corresponds to a cell along the current
     path.  Upon entering find_helper, change the cell's symbol (which had better be a blank) to a plus sign.
     Then, for each adjacent blank, call yourself with that blank cell as the new cell to visit.  if you find
     you have made it out of the maze AND the path length is less than the current shortest path length, then
     save the current maze with the path marked, AND save the path length, and backtrack.  Nothing special
     about the backtracking after a solution b/c we'be been backtracking all along.
*/


/* Theory of Operation
Each instance of the recursion (in find_helper, I think it will be) corresponds to a cell along the current
path.  Upon entering find_helper, change the cell's symbol (which had better be a blank) to a plus sign.
Then, for each adjacent blank, call yourself with that blank cell as the new cell to visit.  if you find
you have made it out of the maze AND the path length is less than the current shortest path length, then
save the current maze with the path marked, AND save the path length, and backtrack.  Nothing special
about the backtracking after a solution b/c we'be been backtracking all along.
*/


// #include "stdafx.h" // VS only

#include <iostream>
#include <fstream>

#include <string>
#include <vector>

#include <climits>
#include <cassert>

using namespace std;

typedef vector<string> maze_t;

maze_t cur_best_path_maze;

int width, height; // maze dimensions

unsigned shortest_path_found;

void print_maze(maze_t & maze)
{
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            cout << maze[row][col];
        }
        cout << endl;
    }
}

bool in_maze(int row, int col) {
    return row >= 0 && row < height &&
           col >= 0 && col < width;
}

bool is_exit(const maze_t & maze, int row, int col) {
    // return row == height - 1 && maze[row][col] == ' ';
    return row == height - 1;
}

// if this path length is shorter, save the maze
// with its path demarcated by '+'
void process_exit(maze_t & maze, unsigned cur_path_len) {
    if (cur_path_len < shortest_path_found) {
        shortest_path_found = cur_path_len;
        cur_best_path_maze = maze;
    }
}

// This is where the magic happens
void find_helper(
        maze_t & maze, unsigned cur_path_len, const int row, const int col)
{
    if (!in_maze(row, col)) {
        return;
    }
    assert(maze[row][col] == ' ');
    cur_path_len++;
    maze[row][col] = '+';
    if (is_exit(maze, row, col)) {
        // debug
        cout << "Found solution ... path length = " << cur_path_len << endl;
        process_exit(maze, cur_path_len);
    }
    else {
        // take next step(s) into the maze

        // Would it have been simpler to just use an array
        // of increments?  Of the nine combinations of loop
        // control variables, only four are actual neighbors
        // (neglecting edges of the grid).

        for (int row_incr = -1; row_incr <= 1; ++row_incr) {
            for (int col_incr = -1; col_incr <= 1; ++col_incr)
            {
                // Visit vertical and horizontal neighbors,
                // but not diagonal ones.  Don't visit yourself.
                // And don't step off the grid.

                if (abs(row_incr) == abs(col_incr)) {
                    continue;  // can't move diagonally or visit self!!
                }

                int r = row + row_incr;
                int c = col + col_incr;
                // cout << "Visiting row " << r << ", column " << col << endl;

                if (!in_maze(row, col)) {
                    continue;
                }

                if (maze[r][c] == ' ') {
                    find_helper(maze, cur_path_len, r, c);
                }
            }
        }
    }
    maze[row][col] = ' ';  // restore state and backtrack
}

void print_shortest_path(const maze_t orig_maze)
{
    shortest_path_found = INT_MAX;  // 32767 which had better be enough!

    maze_t maze = orig_maze; // 'maze' will be our working copy

    // Find entry point and initiate solve
    for (int col = 0; col < width; ++col) {
        if (maze[0][col] == ' ') {
            find_helper(maze, 0, 0, col);
            break;
        }
    }
    print_maze(cur_best_path_maze);
}

// Main for running under VS
// int _tmain(int argc, _TCHAR* argv[])
int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    ifstream ifs(argv[1]);
    string line;
    maze_t orig_maze;  // keep this around, at least during debugging

    while (getline(ifs, line)) {
        // cout << "next input line: " << line << endl;
        orig_maze.push_back(line);
    }

    width = orig_maze[0].size();
    height = orig_maze.size();
    // cout << "width = " << width << ", height = " << height << endl;

    print_shortest_path(orig_maze);

    return 0;
}

// EOF
