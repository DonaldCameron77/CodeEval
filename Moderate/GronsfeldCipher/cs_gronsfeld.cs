// GRONSFELD CIPHER
// CHALLENGE DESCRIPTION:
// 
// You are given a key and an enciphered message.
// The message was enciphered with the following vocabulary:
// 
//  !"#$%&'()*+,-./0123456789:<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz
// Note: The first symbol is space.
// 
// Your task is to decipher the message that was enciphered with the
// Gronsfeld cipher using the given key.
// 
// The Gronsfeld cipher is a kind of the Vigenère cipher and is similar to
// the Caesar cipher. The only difference is that in the Caesar cipher,
// each character is shifted along by the same number, while in the
// Gronsfeld cipher, each character has its own number of shifts. It means
// that the length of key for the Gronsfeld cipher must be the same as the
// length of the message. But since it is difficult to remember such a key,
// especially if the message is long, the key of the message is repeated
// until it has the same length as the message.
// 
// For example:
// 
// For the word "EXALTATION" and the key "31415", the ciphertext is the following:
// 
//   EXALTATION
//   3141531415
// 
//   Enciphering the first letter:
//   'E' + 3 -> 'H'
// 
// Accordingly, enciphered message is the following:
// 
// HYEMYDUMPS
// 
// INPUT SAMPLE:
// 
// The first argument is a file with different test cases (there are
// possible test cases with spaces in enciphered message). Each test case
// contains a key and an enciphered message separated by semicolon.  For
// example:
// 
// 
// 31415;HYEMYDUMPS
// 45162;M%muxi%dncpqftiix"
// 14586214;Uix!&kotvx3
// 
// OUTPUT SAMPLE:
// 
// Print to stdout a deciphered message.
// For example:
// 
// EXALTATION
// I love challenges!
// Test input.
// 
// CONSTRAINTS:
// 
// To decode a message, use the following alphabet:
//   ' !"#$%&\'()*+,-./0123456789:<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'
// 
// The number of test cases is 40.

using System;
using System.IO;
using System.Text.RegularExpressions;
using System.Collections.Generic;
//using System.Linq;
 
namespace GronsfeldCipher
{
    class Program
    {
        const string Charset =
            " !\"#$%&'()*+,-./0123456789:<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

        static char charMap( char c, int offset )
        {
            int startIndex = Charset.IndexOf(c);
            int finishIndex = startIndex - offset;
            if (finishIndex < 0) {
                finishIndex += Charset.Length;
            }
            return Charset[finishIndex];
        }

        static void Main(string[] args)
        {
            using (StreamReader reader = File.OpenText(args[0])) {
                while (!reader.EndOfStream) {
                    string line = reader.ReadLine();
                    if (String.IsNullOrEmpty(line))
                        continue;
                    // We know there will be two, and only two, semicolon-separated strings
                    string[] instrs = Regex.Split(line, ";");
                    string key = instrs[0];
                    string msg = instrs[1];

                    // Console.WriteLine(instrs[0] + ' ' + instrs[1]);

                    int keyIndex = 0;
                    foreach (char c in msg) {
                        char letter = charMap(c, key[keyIndex] - '0');
                        Console.Write(letter);
                        keyIndex = (keyIndex + 1) % key.Length;
                    }
                    Console.WriteLine();
                }
            }
            Console.WriteLine("Press any key to continue ...");
            Console.ReadKey();
        }
    }
}
