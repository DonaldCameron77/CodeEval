

/******************************************************************************************************
    This is CodeEval/Moderate/MagicNumbers - based on initial code in Ruby
 
    CHALLENGE DESCRIPTION:

    There are two wizards, one good and one evil. The evil wizard has captured the princess. The only way to defeat the
    evil wizard is to recite a set of magic numbers. The good wizard has given you two numbers, A and B. Find every magic
    number between A and B, inclusive.

    A magic number is a number that has two characteristics:

    1. No digits repeat.

   2.  Beginning with the leftmost digit, take the value of the digit and move that number of digits to the right.
       Repeat the process again using the value of the current digit to move right again. Wrap back to the leftmost
       digit as necessary. A magic number will visit every digit exactly once and end at the leftmost digit.
 
    For example, consider the magic number 6231.

    Start with 6. Advance 6 steps to 3, wrapping around once (6→2→3→1→6→2→3).
    From 3, advance to 2.
    From 2, advance to 1.
    From 1, advance to 6.

    INPUT SAMPLE:

    The input is a file with each line representing a test case. Each test case consists of
    two integers A and B on a line, separated by spaces. For all test cases 1 <= A <= B <= 10000.

    10 100
    8382 8841

    OUTPUT SAMPLE:

    For each test case print all magic numbers between A and B, inclusive, on one line, separated by spaces.
    If there is no magic number between A and B, print -1.

    13 15 17 19 31 35 37 39 51 53 57 59 71 73 75 79 91 93 95 97
    -1

    CONSTRAINTS:

    The number of test cases is 20.

*******************************************************************************************************/

using System;
using System.IO;
using System.Text.RegularExpressions;
using System.Collections.Generic;
using System.Linq;

class Program
{
    static int[] intToArray(int num)
    {
        List<int> numbers = new List<int>();
        do {
            numbers.Insert(0, num % 10);
            num /= 10;
        } while (num > 0);
        return numbers.ToArray();
    }

    static bool isMagicRule2(int [] digits)
    {
        int numDigits = digits.Length;
        bool [] visited = new bool[numDigits]; // default-initialized to false;
        int curIndex = 0;
        while (true) {
            curIndex = (curIndex + digits[curIndex]) % numDigits;
            if (visited[curIndex]) {
                return false;
            }
            visited[curIndex] = true;
            if (curIndex == 0) { // decision time
                return !visited.Contains(false);
            }
        }
    }

    static void printMagicNumbers(int a, int b)
    {
        bool foundMagic = false;

        for (int c = a; c <= b; ++c)  // c is a "candidate" for magic number
        {
            int[] digits = intToArray(c);

            if (digits.Length != digits.Distinct().Count()) {
                continue; // repeated digit(s) violate rule 1
            }

            if (isMagicRule2(digits)) {
                if (foundMagic) { // suppress trailing blank on output line with magic numbers
                    Console.Write(' ');
                }
                foundMagic = true;
                Console.Write(c);
            }
        }

        if (! foundMagic) {
            Console.Write(-1);
        }
        Console.WriteLine();
    }

    static void Main(string[] args)
    {
        using (StreamReader reader = File.OpenText(args[0]))
        while (!reader.EndOfStream)
        {
            string line = reader.ReadLine();
            if (String.IsNullOrEmpty(line))
                continue;
            // We know there will be two, and only two, blank-separated ints in string form
            string[] instrs = Regex.Split(line, " ");
            int a = Convert.ToInt32(instrs[0]);
            int b = Convert.ToInt32(instrs[1]);
            printMagicNumbers(a, b);

            //foreach (string s in instrs) {
            //    Console.Write(s + ' ');
            //}
            //Console.Write(instrs[0] + ' ');
            //Console.Write(instrs[1] + ' ');
            //Console.WriteLine();
        }
        Console.WriteLine("Press any key to continue ...");
        Console.ReadKey();
    }
}