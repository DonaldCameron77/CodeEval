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

#include <iostream>
#include <fstream>

using namespace std;

const string Charset =
        " !\"#$%&'()*+,-./0123456789:<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

char char_map( char c, int offset ) {
    int start_index = Charset.find(c); // no error checking
    int finish_index = start_index - offset;
    if (finish_index < 0) {
        finish_index = Charset.length() + finish_index;
    }
    return Charset[finish_index];
}

int main(int argc, char *argv[]) {
    ifstream stream(argv[1]);
    string line;
    while (getline(stream, line))
    {
        // Split input line at ';' into message and key.
        // We can't simply replace the semicolon by a
        // blank and use isstringstream, as the message
        // can contain blanks

        unsigned semipos = line.find(';');
        string key = line.substr(0, semipos);
        string msg = line.substr(semipos + 1, string::npos);

        int key_index = 0;
        for (unsigned i = 0; i < msg.length(); ++i) {
            char letter = char_map( msg[i], key[key_index] - '0' );
            key_index = (key_index + 1) % key.length();
            cout << letter;
        }

        cout << endl;
    }
    return 0;
}

// EOF
