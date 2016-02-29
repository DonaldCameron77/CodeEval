/*
STRING PERMUTATIONS - CodeEval Hard challenge

CHALLENGE DESCRIPTION:

Write a program to print out all the permutations of a string in
alphabetical order. We consider that digits < upper case letters < lower
case letters. The sorting should be performed in ascending order.

INPUT SAMPLE:

Your program should accept as its first argument a path to a file
containing an input string, one per line. E.g.

hat
abc
Zu6

OUTPUT SAMPLE:

Print to stdout, permutations of the string, comma separated, in
alphabetical order. E.g.

aht,ath,hat,hta,tah,tha
abc,acb,bac,bca,cab,cba
6Zu,6uZ,Z6u,Zu6,u6Z,uZ6

*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

void cswap(string & s, unsigned i, unsigned j) {
    const char tmp = s[i];
    s[i] = s[j];
    s[j] = tmp;
}

void permute_and_print(string s, unsigned start, bool & first)
{
    if (start == s.size() - 1) {
	if (first) {
	    first = false;
	    cout << s;
	}
	else {
	     cout << ',' << s;
	}
    }
    else {
	for (unsigned i = start; i < s.size(); ++i) {
	    permute_and_print(s, start + 1, first);
	    cswap(s, start, i+1); // useless on last trip of loop when we'll just exit
	}
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
	cout << "usage: " << argv[0] << "<filename>\n";
	return 1;
    }

    ifstream ifs(argv[1]);
    string line;

    while (getline(ifs, line))
    {
	sort(line.begin(), line.end());
	bool first = true;
	permute_and_print(line, 0, first);
	cout << endl;
	    
    }
}

// EOF
