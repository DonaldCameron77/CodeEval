/*
CLOSEST PAIR - CodeEval Hard challenge
CHALLENGE DESCRIPTION:

Credits: Programming Challenges by Steven S. Skiena and Miguel A. Revilla 

You will be given the x/y co-ordinates of several locations. You will be
laying out 1 cable between two of these locations. In order to minimise
the cost, your task is to find the shortest distance between a pair of
locations, so that pair can be chosen for the cable installation.

INPUT SAMPLE:

Your program should accept as its first argument a path to a filename.
The input file contains several sets of input. Each set of input starts
with an integer N (0<=N<=10000), which denotes the number of points in
this set. The next N line contains the coordinates of N two-dimensional
points. The first of the two numbers denotes the X-coordinate and the
latter denotes the Y-coordinate. The input is terminated by a set whose
N=0. This set should not be processed. The value of the coordinates will
be less than 40000 and non-negative. eg.

5
0 2
6 67
43 71
39 107
189 140
0

OUTPUT SAMPLE:

For each set of input produce a single line of output containing a
floating point number (with four digits after the decimal point) which
denotes the distance between the closest two points. If there is no such
two points in the input whose distance is less than 10000, print the
line INFINITY. eg.

36.2215

*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

double pythag( int x1, int y1, int x2, int y2 ) {
    return sqrt( pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "usage: " << argv[0] << "<filename>\n";
        return 1;
    }

    ifstream ifs(argv[1]);
    unsigned npoints;
    vector<pair<int, int> > pvec;

    while (ifs >> npoints)
    {
        if (npoints == 0) break;
        pvec.clear();
        for (unsigned i = 1; i <= npoints; ++i) {
            int x, y;
            ifs >> x >> y;
            pvec.push_back( pair<int,int>(x, y));
        }

        double min_distance = 1000000; // big enough(?)

        for (unsigned int i = 0; i < pvec.size() - 1; ++ i) {
            for (unsigned int j = i + 1; j < pvec.size(); ++ j) {
                 double cur_dist =
                        pythag (pvec[i].first, pvec[i].second, pvec[j].first, pvec[j].second);
                min_distance = min(min_distance, cur_dist);
            }
        }
        
        cout << fixed << setprecision(4);
        if (min_distance < 10000)
            cout << min_distance;
        else
            cout << "INFINITY";
        cout << endl;
    }
}
