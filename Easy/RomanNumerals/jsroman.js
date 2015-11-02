
/* CodeEval Easy challenge - given integer, print Roman Numeral representation

CHALLENGE DESCRIPTION:

Many persons are familiar with the Roman numerals for relatively small
numbers. The symbols I (capital i), V, X, L, C, D, and M represent the
decimal values 1, 5, 10, 50, 100, 500 and 1000 respectively. To
represent other values, these symbols, and multiples where necessary,
are concatenated, with the smaller-valued symbols written further to the
right. For example, the number 3 is represented as III, and the value 73
is represented as LXXIII. The exceptions to this rule occur for numbers
having units values of 4 or 9, and for tens values of 40 or 90. For
these cases, the Roman numeral representations are IV (4), IX (9), XL
(40), and XC (90). So the Roman numeral representations for 24, 39, 44,
49, and 94 are XXIV, XXXIX, XLIV, XLIX, and XCIV, respectively. 

Write a program to convert a cardinal number to a Roman numeral.

INPUT SAMPLE:

Your program should accept as its first argument a path to a filename.
Input example is the following

159
296
3992

Input numbers are in range [1, 3999]

OUTPUT SAMPLE:

Print out Roman numerals.

CLIX
CCXCVI
MMMCMXCII
*/

// this is const too ...
var rns = []; // 2-dim array of roman numeral tokens

// Roman numeral notation did not require or use a zero.
rns[0] = ["Error", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"];
rns[1] = ["Error", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"];
rns[2] = ["Error", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"];
rns[3] = ["Error", "M", "MM", "MMM", "Error", "Error", "Error", "Error", "Error", "Error"];

var fs  = require("fs");

fs.readFileSync(process.argv[2]).toString().split('\n').forEach(function (line)
{
    var num = Number(line);

    if (num !== 0)
    {    // we get a phanton last line which converts to 0. Do we need JS equivalent of chomp?
        var roman = [];
        var digitNumber = 0;

        while (num !== 0)
        {
            var newDigit = num % 10;
            num = Math.floor(num / 10);
            if (newDigit !== 0) {
                roman.push(rns[digitNumber][newDigit]);
                // nicer than using indexing to create new elements in the roman array
            }
            digitNumber += 1;
        }
        console.log(roman.reverse().join(""));
    }
});
