using System;
using System.IO;
using System.Collections.Generic;

class Program
{
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

    static void printAnswer(double ans)
    {
        // Console.WriteLine(ans < 10000 ? ans.ToString() : "INFINITY");
        Console.WriteLine(ans < 10000
                        ? ans.ToString("F4")
                        : "INFINITY");
    }

    static double pythag(int x1, int y1, int x2, int y2)
    {
        return Math.Sqrt(Math.Pow(x1 - x2, 2) + Math.Pow(y1 - y2, 2));
    }

    static double findClosestPair(List<Point> points)
    {   
        int psize = points.Count;
        double minDistance = 1000000;
        for (int i = 0; i < psize - 2; ++i) {
            for (int j = i + 1; j < psize - 1; ++j) {
                double curDistance = pythag(points[i].X, points[i].Y, points[j].X, points[j].Y);
                if (curDistance < minDistance) {
                    minDistance = curDistance;
                }
            }
        }
        return minDistance;
    }

    static void Main(string[] args)
    {
        using (StreamReader reader = File.OpenText(args[0]))
        {
            bool first = true;
            List<Point> points = new List<Point>();
            int nPoints = 0;
            int ptsSeen = 0;
            while (!reader.EndOfStream)
            {
                // This is a state machine, basically, which follows my JavaScript
                // implementation.  See pseudo-regex below for format/pattern of input.

                // TODO: it would be MUCH simpler to just have separate sections or methods
                // for reading each part/state of the input, which has the form (where / represents newline)
                //    (count / (pointX' 'pointY/)+)+ / 0 <eof>
                // (Ignore blanks unless quoted).

                string line = reader.ReadLine();

                if (String.IsNullOrEmpty(line)) {
                    continue;
                }
                // Console.WriteLine(line); // debug
                if (line == "0") {
                    // Development only
                    Console.WriteLine("Press any key to exit ...");
                    Console.ReadKey();
                    // Development only
                    return;
                }
                if (first) {
                    nPoints = int.Parse(line);
                    first = false;
                }
                else {
                    ++ptsSeen;
                    string[] strPointArr = line.Split(' ');
                    //int x = int.Parse(strPointArr[0]);      // could do without temps x, y
                    //int y = int.Parse(strPointArr[1]);
                    //Point curPoint = new Point(x, y);
                    Point curPoint = new Point(int.Parse(strPointArr[0]), int.Parse(strPointArr[1]));
                    points.Add(curPoint);
                    if (ptsSeen == nPoints) {
                        printAnswer(findClosestPair(points));
                        first = true;
                        points.Clear();
                        nPoints = 0;
                        ptsSeen = 0;
                    }
                }
            }
        }   
    }
}

class Point
{
    public int X { get; set; }
    public int Y { get; set; }

    public Point(int x, int y) { X = x; Y = y; }
}
