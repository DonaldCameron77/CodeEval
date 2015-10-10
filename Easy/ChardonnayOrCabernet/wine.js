
// CHARDONNAY OR CABERNET - CodeEval Easy challenge
// 
// CHALLENGE DESCRIPTION:
// 
// Your good friend Tom is admirer of tasting different types of fine
// wines. What he loves even more is to guess their names. One day, he was
// sipping very extraordinary wine. Tom was sure he had tasted it before,
// but what was its name? The taste of this wine was so familiar, so
// delicious, so pleasant… but what is it exactly? To find the answer, Tom
// decided to taste the wines we had. He opened wine bottles one by one,
// tasted different varieties of wines, but still could not find the right
// one. He was getting crazy, “No, it’s not that!” desperately breaking a
// bottle of wine and opening another one. Tom went off the deep end not
// knowing what this wine was. Everything he could say is just several
// letters of its name. You can no longer look at it and decided to help
// him. 
// 
// Your task is to write a program that will find the wine name, containing
// all letters that Tom remembers.
// 
// INPUT SAMPLE:
// 
// The first argument is a path to a file. Each line includes a test case,
// which contains names of wines and letters that Tom remembers. Names and
// letters are separated by a vertical bar '|'.
// 
// For example:
// 
// Cabernet Merlot Noir | ot
// Chardonnay Sauvignon | ann
// Shiraz Grenache | o
// 
// OUTPUT SAMPLE:
// 
// You should print wine names, containing all letters that Tom remembered.
// Letters can be anywhere in wine names. If there is no name with all
// letters, print False.
// 
// For example:
// 
// Merlot
// Chardonnay Sauvignon
// False
// 
// CONSTRAINTS:
// 
// Wine name length can be from 2 to 15 characters.
// Number of letters that Tom remembered does not exceed 5.
// Number of wine names in a test case can be from 2 to 10.
// If there is no wine name containing all letters, print False.
// The number of test cases is 40.


///////////// my standard utilities for dealing with strings ///////////

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

// wineArr is an array of strings
// letters is an array of char
// print wineArr[k] iff all characters in letters appear in it.
//
// Note: I am interpreting this to mean that if there are two instances
// of letter x in the letters array, then there must be two x's in
// wineArr[k] or it doesn't qualify
function checkWinesVsLetters(wineArr, letters)
{
    first = true;
    outStr = "";
    for (var k = 0; k < wineArr.length; ++k)
    {
        if (checkAWine(wineArr[k], letters)) {
            if (first) {
                first = false;
                outStr = wineArr[k];
            }
            else {
                outStr +=  " " + wineArr[k];
            }
        }
    }
    if (outStr === "") {
        outStr = "False";
    }
    console.log(outStr);
}

function checkAWine(wine, letters)
{
    var mask = []; // we'll set mask[k] to true once we have used wineArr[k] in a match
    for (var i = 0; i < wine.length; ++i) {
        mask[i] = false;
    }

    for (var x = 0; x < letters.length; ++x)
    {
        var curLetter = letters[x];
        var matchedCurLetter = false;
        for (var i = 0; i < wine.length; ++i)
        {
            if (!mask[i] && curLetter === wine[i])
            {
                if (x === letters.length - 1) {
                    return true;
                }
                else {
                    mask[i] = matchedCurLetter = true; 
                    break;
                }
            }
        }
        if (!matchedCurLetter) {
            return false;
        }
    }
    console.log("check A Wine : unexpected completion of outer loop");
}

var fs  = require("fs");

fs.readFileSync(process.argv[2]).toString().split('\n').forEach(function (line)
{
    if (line !== "")  // or if (line) ... for truthy/falsy
    {
        var inArr = mySplit(line, '|');
        var wineArr = mySplit(inArr[0], " ");
        var letters = mySplit(inArr[1], "");
        // console.log(wineArr);
        // console.log(letters);
        checkWinesVsLetters(wineArr, letters);
        // console.log();
    }
});

// eof
