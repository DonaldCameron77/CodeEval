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

function chomp(raw_text) {
    return raw_text.replace(/(\n|\r)+$/, '');
}

// trim not universally supported, and does nothing in node currently
// 9/2015
function myTrim(x) {
    return x.replace(/^\s+|\s+$/gm,'');
}

// built-in split can add/leave whitespace
function mySplit(s, c) {
    var wrkArr = s.split(c);
    var outArr = [];
    for (var i = 0; i < wrkArr.length; ++i) {
        if (wrkArr[i]) {    // reject 'falsy' values
            outArr[i] = myTrim(wrkArr[i]);
        }
    }
    return outArr;
}

function pythag( x1, y1, x2, y2 ) {
    return Math.sqrt( Math.pow(x1 - x2, 2) + Math.pow(y1 - y2, 2));
}

// arr is an array of strings representing integers.
// convert the elements to integers and return in a new array
function numericize(arr) {
    var newArr = [];
    for (var i = 0; i < arr.length; ++i) {
        newArr[i] = Number(arr[i]);
    }
    return newArr;
}

// paintArr is an array of integer pairs representing x, y coordinates.
// Find the two pairs closest to each other, and return the distance.
function findClosestPair(pointArr) {
    var minDistance = 1000000; // infinity, effectively
    for (var i = 0; i < pointArr.length - 1; ++i) {
        for (var j = i + 1; j < pointArr.length; ++j) {
            curDist = pythag(pointArr[i][0], pointArr[i][1], pointArr[j][0], pointArr[j][1]);
            minDistance = Math.min(minDistance, curDist);
        }
    }
    return minDistance;
}

// d is a distance, as a floating point number.
// if d is greater than or equal to 10,000 print INFINITY
// otherwise print d to 4 decimal places

function printAnswer(d) {
    console.log( d < 10000 ? d.toFixed(4) : "INFINITY" );
}

var first = true;
var npoints;
var n = 0;
var pointArr = [];

var fs  = require("fs");
fs.readFileSync(process.argv[2]).toString().split('\n').forEach(function (line)
{
    if (chomp(line) === '0') return;
    if (first) {
        npoints = Number(line);
        first = false;
    }
    else {
        ++n;
        var point = line.split(" ");
        point = numericize(point);
        pointArr.push(point);
        if (n === npoints) {
            printAnswer( findClosestPair( pointArr ));
            // now reinitialize for next set
            first = true;
            n = 0;
            pointArr = [];
        }
    }
});

// EOF
