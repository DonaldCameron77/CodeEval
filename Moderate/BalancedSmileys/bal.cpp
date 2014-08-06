/*
BALANCED SMILEYS - CodeEval Moderate challenge

CHALLENGE DESCRIPTION:

Credits: This problem appeared in the Facebook Hacker Cup 2013 Hackathon. 

Your friend John uses a lot of emoticons when you talk to him on
Messenger. In addition to being a person who likes to express himself
through emoticons, he hates unbalanced parenthesis so much that it makes
him go :(. 

Sometimes he puts emoticons within parentheses, and you find it hard to
tell if a parenthesis really is a parenthesis or part of an emoticon. A
message has balanced parentheses if it consists of one of the following: 

- An empty string "" 
- One or more of the following characters: 'a' to 'z', ' ' (a space) or ':' (a colon) 
- An open parenthesis '(', followed by a message with balanced parentheses, followed by a close parenthesis ')'.
- A message with balanced parentheses followed by another message with balanced parentheses. 
- A smiley face ":)" or a frowny face ":(" 

Write a program that determines if there is a way to interpret his
message while leaving the parentheses balanced.

INPUT SAMPLE:

Your program should accept as its first argument a path to a filename.
Each line in this file contains a message that you got from John. E.g.

:((
i am sick today (:()
(:)
hacker cup: started :):)
)(

OUTPUT SAMPLE:

Print out the string "YES"/"NO" (all quotes for clarity only) stating
whether or not it is possible that the message had balanced parentheses.
E.g.

NO
YES
YES
YES
NO
*/

/*/////////////////////////////////////////////////////////////////////
Theory of Operation:

Consider the simple way we scan for balanced parens when there
is only one possible pair of tokens, e.g., '(' and ')'.  We can base our
solution on that.

The classic O(n) solution is to maintain two quantities, call them
maxOpen and minOpen.

Both are initially zero.
Whenver we see a '(' we increment max_open.
Whenever we see a '(' not preceded by a colon, we increment min_open.
Whenever we see a ')' we decrement min_open  (without letting it become less than zero).
Whenever we see a ')' not preceded by a colon, we decrement max_open

If max_open ever goes negative, fail immediately.
And at the end of scan, we have the additional constraint that min_open
must be zero.

Credit to the Facebook Cup staff for the solution concept.

/*///////////////////////////////////////////////////////////////////*/


#include <iostream>
#include <fstream>

using namespace std;

bool balanced_smileys(string & line) {
    int max_open = 0, min_open = 0;
    for (unsigned i = 0; i < line.length(); ++i) {
        char ch = line[i];
        if ( ch == '(' ) {
            ++max_open;
            if (i == 0 || line[i-1] != ':') {
                ++min_open;
            }
        }
        else if ( ch == ')' ) {
            min_open = max(0, min_open-1);
            if (i == 0 || line[i-1] != ':') {
                --max_open;
                if (max_open < 0)
                    return false;
            }
        }
    }
    // Note we're assured max_open >= 0 here
    return min_open == 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
            cout << "usage: " << argv[0] << "<filename>\n";
            return 1;
    }

    ifstream ifs(argv[1]);
    string line;

    while (getline(ifs, line)) {
        bool result = balanced_smileys(line);
        if (result) {
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
    } // while getline
}

// EOF
