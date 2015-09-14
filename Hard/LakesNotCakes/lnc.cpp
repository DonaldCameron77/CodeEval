// LAKES, NOT CAKES - CodeEval Hard challenge
//          (seems not that hard at first glance 8-)
// CHALLENGE DESCRIPTION:
// 
// It was a dark and stormy night when Alice was wandering in the black
// forest. The rain fell in torrents into deep lakes scattered all over the
// area… Wait! Lakes… forest…? Really? Well, yeah, it’s not a true horror
// story, but it is fits our challenge perfectly. So, you have a map of the
// forest. You are sure there are some lakes in there, but you do not know
// their number. 
// 
// Write a program that will count how many lakes are in the forest. We
// count all adjacent o symbols as one lake (by adjacent we mean symbols
// that are located one cell up, down, left, right, or diagonally from the
// needed symbol).
// 
// INPUT SAMPLE:
// 
// The first argument is a path to a file. Each line includes a test case,
// which contains a map of the forest of different size. Forest areas are
// separated by a vertical bar |. 
// 
// # - forest 
// o - lake
// 
// For example:
// 
// o # o | # # # | o # o
// o # o | # o # | o # o
// 
// OUTPUT SAMPLE:
// 
// Print the number of lakes for each test case.
// 
// For example:
// 4
// 1
// 
// CONSTRAINTS:
// 
// A forest may be of different width and height from 3 to 30 symbols.
// Diagonal symbols are also counted as adjacent.
// The number of test cases is 40.

#include <iostream>
#include <fstream>

#include <vector>
#include <algorithm>

using namespace std;

struct cell_data {
    const char terrain_type;
    bool visited;
    cell_data( char gtype ) : terrain_type(gtype), visited(false) {}
};

typedef vector< vector< cell_data > > t_grid;

#ifdef DEBUG
void print_forest(const t_grid & grid)
{
    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[row].size(); ++ col) {
            cout << grid[row][col].terrain_type;
        }
        cout << "\n";
    }
    cout << endl;
}
#endif // DEBUG

void parse_forest(const string & input_line, t_grid & grid)
{
    vector< cell_data > gr; // gr is a grid row.  It's reset below when
                            // a '|' is encountered in the input

    for (unsigned i = 0; i < input_line.length(); ++i)
    {
        cell_data cur( input_line[i] );

        switch (cur.terrain_type) {
            case ' ':
                continue;
            case 'o':
            case '#':
                gr.push_back(cur);
                break;
            case '|':
                grid.push_back(gr);
                gr.clear();
                continue;
            default:
                cerr << "unexpected character in input line" << endl;
        }
    }
}

void mark_reachable_water(t_grid & grid, int row, int col)
{
    if (grid[row][col].terrain_type != 'o')
        return;

    grid[row][col].visited = true;

    // Brute force and has some inefficiencies.
    // Should investigate "strongly connected region" algorithms
    for (int r = max(row - 1, 0); r <= min(row + 1, int(grid.size()-1)); ++r) {
        for (int c = max(col - 1, 0); c <= min(col + 1, int(grid[r].size()-1)); ++c)
        {
            if (grid[r][c].terrain_type == 'o' &&
                            ! grid[r][c].visited)
            {
                mark_reachable_water(grid, r, c);
            }
        }
    }
}

unsigned count_lakes(t_grid & grid)
{
    unsigned num_lakes = 0;

    for (unsigned row = 0; row < grid.size(); ++ row)
    {
        for (unsigned col = 0; col < grid[row].size(); ++col)
        {
            cell_data & cur = grid[row][col]; // temp aids debugging
            if (cur.terrain_type == 'o' && ! cur.visited) {
                // cur.visited = true; // mark_reachable will do it
                ++num_lakes;
                mark_reachable_water(grid, row, col);
            }
        }
    }
    return num_lakes;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    ifstream ifs(argv[1]);
    string line;

    while (getline(ifs, line))
    {
        // we're going to append a '|' to the line as a sentinel
        line += '|';
#ifdef DEBUG
        cout << line << endl;
#endif // DEBUG

        t_grid grid;
        parse_forest(line, grid);

#ifdef DEBUG
        print_forest(grid);
#endif // DEBUG

        unsigned num_lakes = count_lakes(grid);
        cout << num_lakes << endl;
    }
}

// EOF
