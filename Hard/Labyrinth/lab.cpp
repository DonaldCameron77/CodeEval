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

    Each instance of the recursion (in find_helper, I think it will be)
    corresponds to a cell along the current path.  Upon entering
    find_helper, change the cell's symbol (which had better be a blank) to a
    plus sign.  Then, for each adjacent blank, call yourself with that blank
    cell as the new cell to visit.  if you find you have made it out of the
    maze AND the path length is less than the current shortest path length,
    then save the current maze with the path marked, AND save the path
    length, and backtrack.  Nothing special about the backtracking after a
    solution b/c we'be been backtracking all along.

================== Um, no 8=( ... fails for large examples such as the
    101x101 test case our CodeEval friends threw at it

    Trying breadth first search, which turns out to be a simplified variant of
    Djikstra's algorithm.  Start at the entrance, and enqueue the entrance cell.
    At each iteration, pop the queue and enqueue the popped cell's neighbors
    which have not yet been visited. Whenever you hit the exit point, you're done
    except for walking back the shortest path.  To allow that, you have to save
    the predecessor of each cell along this path.

    This should work because

    1. You are not a single rat trying to find the exit.  You are many rats
    ... as many as are needed.  

    2. At any cell the maze may offer a choice.  You clone rats to explore
    each choice in parallel.

    3. At the start of any iteration, all the rats are the same distance
    from the entrance.

*/

#include <iostream>
#include <fstream>

#include <string>
#include <vector>
#include <queue>

#include <cassert>

using namespace std;

typedef vector<string> maze_t;

int width, height; // maze dimensions

void print_maze(maze_t & maze)
{
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            cout << maze[row][col];
        }
        cout << endl;
    }
}

// info about corresponding cell in maze

struct duplet {
    int row, col;
};

struct cell_info_t {
    bool visited;
    duplet own;       // need indices for cell popped off queue
    duplet came_from; // need to know predecessor on best path
    cell_info_t() : visited(false) {
        own.row = own.col = came_from.row = came_from.col = -1;
    }
};

typedef vector<vector<cell_info_t>> info_arr_t;

void init_info_arr(info_arr_t & info_arr)
{
    // initialize the parallel grid of information
    cell_info_t cell_info;
    vector<cell_info_t> info_row(width, cell_info);
    for (int r = 0; r < height; ++r) {
        info_arr.push_back(info_row);
    }
}

int find_entry(maze_t & maze) {
    for (int col = 0; col < width; ++col) {
        if (maze[0][col] == ' ') {
            return col;
        }
    }
    return -1;  // shut up compiler warning
}

bool in_maze(int row, int col) {
    return row >= 0 && row < height &&
           col >= 0 && col < width;
}

bool is_exit(int row, int col) {
    // We know there is only one blank cell in the bottom row.
    // Could pass maze in too and assert current cell is blank
    return row == height - 1;
}

void process_exit(
    maze_t & maze, info_arr_t & info_arr, int exit_row, int exit_col) {
    // mark path back to the entrance with '+'
    int row = exit_row;
    int col = exit_col;

    // note the entrance row must be in row 0, and there can only
    // be one entrance.  Note row will get set to -1 on the
    // final trip through the loop.
    do {
        maze[row][col] = '+';
        cell_info_t cell_info = info_arr[row][col];
        // row = info_arr[row][col].came_from.row;
        // col = info_arr[row][col].came_from.col;
        row = cell_info.came_from.row;
        col = cell_info.came_from.col;
    } while (row >= 0);
}

void process_neighbor(
    maze_t & maze, info_arr_t & info_arr, queue<cell_info_t> & info_queue,
    int pred_row, int pred_col, int own_row, int own_col)
{
    // For each unvisited neighbor, set 'own' to its coordinates,
    // 'came_from' to pred_row, pred_col, and set visited = true.
    // Append it to the back of the queue

    if (! in_maze(own_row, own_col) ||
        maze[own_row][own_col] != ' ' ||
        info_arr[own_row][own_col].visited) {
        return;
    }

    info_arr[own_row][own_col].visited = true;
    info_arr[own_row][own_col].own.row = own_row;
    info_arr[own_row][own_col].own.col = own_col;
    info_arr[own_row][own_col].came_from.row = pred_row;
    info_arr[own_row][own_col].came_from.col = pred_col;

    info_queue.push(info_arr[own_row][own_col]);
}

void print_shortest_path(const maze_t & orig_maze)
{
    maze_t maze = orig_maze;    // 'maze' is working copy of grid

    info_arr_t info_arr;        // parallel grid of cell information
    init_info_arr(info_arr);

    queue<cell_info_t> info_queue;

    int entry_pt_col = find_entry(maze);  // indices are then 0, col
    info_arr[0][entry_pt_col].visited = true;
    info_arr[0][entry_pt_col].own.row = 0;
    info_arr[0][entry_pt_col].own.col = entry_pt_col;
    // came_from will be -1, -1 as it should be
    info_queue.push(info_arr[0][entry_pt_col]);
    
    while (true)
    {
        cell_info_t cur_info = info_queue.front();
        info_queue.pop();
        assert(cur_info.visited == true);
        int cur_row = cur_info.own.row;
        int cur_col = cur_info.own.col;

        if (is_exit(cur_row, cur_col)) {
            process_exit(maze, info_arr, cur_row, cur_col);
            print_maze(maze);
            return;  // yippee we're done
        }
        else {
            // try neighbors clockwise starting from midnight (12 hr clock 8-)
            process_neighbor(maze, info_arr, info_queue,  cur_row, cur_col, cur_row - 1, cur_col);
            process_neighbor(maze, info_arr, info_queue,  cur_row, cur_col, cur_row, cur_col + 1);
            process_neighbor(maze, info_arr, info_queue,  cur_row, cur_col, cur_row + 1, cur_col);
            process_neighbor(maze, info_arr, info_queue,  cur_row, cur_col, cur_row, cur_col - 1);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    ifstream ifs(argv[1]);
    string line;
    maze_t orig_maze;

    while (getline(ifs, line)) {
        orig_maze.push_back(line);
    }

    width = orig_maze[0].size();
    height = orig_maze.size();

    print_shortest_path(orig_maze);

    return 0;
}

// EOF
