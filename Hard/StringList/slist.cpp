/*
STRING LIST
CHALLENGE DESCRIPTION:

Credits: Challenge contributed by Max Demian. 

You are given a number N and a string S. Print all of the possible ways
to write a string of length N from the characters in string S, comma
delimited in alphabetical order.

INPUT SAMPLE:

The first argument will be the path to the input filename containing the
test data. Each line in this file is a separate test case. Each line is
in the format: N,S i.e. a positive integer, followed by a string (comma
separated). E.g.

1,aa
2,ab
3,pop

OUTPUT SAMPLE:

Print all of the possible ways to write a string of length N from the
characters in string S comma delimited in alphabetical order, with no
duplicates. E.g.

a
aa,ab,ba,bb
ooo,oop,opo,opp,poo,pop,ppo,ppp
*/

/*
    note: SDS's TINY Ruby solution merits further study!
*/

#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

void print_vector_of_strings( const vector<string> & svec ) {
    bool first = true;
    for (auto it = svec.begin(); it != svec.end(); ++it) {
        if (first) { first = false; } else { cout << ','; }
        cout << *it;
    }
    cout << "\n";
}

void make_strings( unsigned len, const string & chars, string cur_string, vector<string> & svec )
{
    if (len == 0) {
        svec.push_back(cur_string);
        return;
    }

    for (unsigned i = 0; i < chars.length(); ++i) { // could use iterator on 'chars'
        cur_string.push_back(chars[i]); // could allocate this entry just once and
                                        // just index in loop, but this is clear at least
        make_strings(len - 1, chars, cur_string, svec);
        cur_string.pop_back();
    }
}

// from the characters in 'chars', which may have duplicates (e.g., // p,o,p),
// generate all possible strings of length len, and then sort the result
// and remove duplicates
void make_strings( unsigned len, const string & chars, vector<string> & svec ) {
    string cur_string;
    make_strings(len, chars, cur_string, svec); 
    sort( svec.begin(), svec.end() );
    vector<string>::iterator it;
    it = unique( svec.begin(), svec.end() );
    svec.resize( distance( svec.begin(), it ) );
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "usage: " << argv[0] << "<filename>\n";
        return 1;
    }

    ifstream ifs(argv[1]);
    string line;

    while (getline(ifs, line)) {
        unsigned len;
        istringstream iss(line);
        iss >> len;
        iss.ignore();
        string chars;
        iss >> chars;
        // cout << len << ' ' << chars << endl;
        vector<string> svec;
        make_strings(len, chars, svec);
        print_vector_of_strings(svec);
    } // while getline
}

// EOF
