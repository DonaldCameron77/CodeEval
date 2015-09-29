// FIND THE HIGHEST SCORE - CodeEval Easy challenge
// CHALLENGE DESCRIPTION:
// 
// You decided to hold a banquet in honor of the World Art Day, where you
// invited all designers and artists that you know. During the banquet, you
// decided to find out which art movement and style the ordinary people
// like most of all, and whose works can get the highest score. To find the
// answer, you decided to hold an exhibition, where viewers will be able to
// evaluate each painting and vote for or against it. Each artist should
// create one work per each art movement.  After the exhibition, the
// participants calculated votes that they received for each painting and
// inserted them in the table. But, they could not determine which movement
// has won and whose work received the highest score, so they asked you to
// help.  You need to determine and print the highest score of each
// category in the table.
// 
// Example:
// 
//             Baroque     Surrealist  Modern
// Klimt           72          64        150
// Rembrandt      100          18         33
// Dali            13         250         -6
// MAXIMUM        100         250        150
// 
// Your job is to find the maxima of each column
// 
// INPUT SAMPLE:
// 
// The first argument is a path to a file. Each line includes a test case
// with a table. Table rows are separated by pipes '|'. All table rows
// contain scores for each category, so all lines are of an equal length.
// 
// For example:
// 
// 72 64 150 | 100 18 33 | 13 250 -6
// 10 25 -30 44 | 5 16 70 8 | 13 1 31 12
// 100 6 300 20 10 | 5 200 6 9 500 | 1 10 3 400 143
// 
// OUTPUT SAMPLE:
// 
// You need to print the highest score for each category.
// 
// For example:
// 
// 
// 100 250 150
// 13 25 70 44
// 100 200 300 400 500
// 
// CONSTRAINTS:
// 
// All lines in a test case are of an equal length.
// The number of participants can be from 2 to 10 people.
// The number of categories can be from 4 to 20.
// The number of points for one picture can be from -1000 to 1000.
// The number of test cases is 40.
// 
// ===============
// 
// Implementation: this is a snap in Ruby (I think!).
// In C++, it would be nice to have a class to handle variable
// sized two dimensional arrays (which is what we have here).
//
// ================

///////////// my standard utilities for dealing with strings ///////////

// chomp from http://3dmdesign.com/development/chomp-for-javascript
// (not needed, so far)
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

////////////////////////////////////////////////////////////////////////

/////// Standard CodeEval printing - suppress trailing blanks

// Print an array of integers, blank separated, but suppress trailing blank
// Harder than it should be, b/c console.log always appends a newline

function printIntArray(a) {
    var first = true;
    var printMe = "";
    for (var i = 0; i < a.length; ++i) {
        if (first) {
            printMe = a[i];
            first = false;
        }
        else {
            printMe += " " + a[i];
        }
    }
    console.log(printMe);
}

// rowArr is an array of strings, each of which is a set of blank-separated
// integers. This is a rectangular (i.e., not // jagged) array.
// Find the max of each column and return it as an array of int.

function findColumnMaxima(rowArr)
{
    // split elems of each row into here - will be 2-dim array
    var rowVal = new Array(rowArr.length);

    for (var i = 0; i < rowArr.length; ++i) {
        rowVal[i] = mySplit(rowArr[i], " ");
    }

    var maxArr = [];

    // init array of max column elems with elems of first row.
    for (var i = 0; i < rowVal[0].length; ++i) {
        maxArr[i] = Number(rowVal[0][i]); 
    }
    
    // now get the column maxima into maxArr

    for (var col = 0; col < rowVal[0].length; ++col) {
        for (var row = 1; row < rowVal.length; ++row) {
            var trialVal = Number(rowVal[row][col]);
            if (trialVal > maxArr[col]) {
                maxArr[col] = trialVal;
            }
        }
    }
    return maxArr;
}

var fs  = require("fs");

fs.readFileSync(process.argv[2]).toString().split('\n').forEach(function (line)
{
    if (line != "")  // or if (line) ... for truthy/falsy
    {
        var inArr = mySplit(line, '|');
        var maxArr = findColumnMaxima(inArr);
        printIntArray(maxArr);
    }
});

// eof

