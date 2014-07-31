/*
STRING SEARCHING - CodeEval Hard challenge
CHALLENGE DESCRIPTION:

You are given two strings. Determine if the second string is a substring
of the first (Do NOT use any substr type library function). The second
string may contain an asterisk(*) which should be treated as a regular
expression i.e. matches zero or more characters. The asterisk can be
escaped by a \ char in which case it should be interpreted as a regular
'*' character. To summarize: the strings can contain alphabets, numbers,
* and \ characters.

INPUT SAMPLE:

Your program should accept as its first argument a path to a filename.
The input file contains two comma delimited strings per line. E.g.

Hello,ell
This is good, is
CodeEval,C*Eval
Old,Young
OUTPUT SAMPLE:

If the second string is indeed a substring of the first, print out a
'true'(lowercase), else print out a 'false'(lowercase), one per line.

E.g.

true
true
true
false

#########################################################################

See above for possibility of '*' wildcard in pat.
The * should be treated like .* in normal regex syntax.

* is greedy, which leads to backtracking situations in a general
regex implementationi (e.g., subject = "abfoocdc" and pattern = "ab*cd",
where the first match attempted is "abfoocdc" - with no following 'd',
one must back up to * matching "foo" only, not "foocd" ) ...
but here we're only interested in a correct Boolean, so we
can take the leftmost match.  No need to start with the
rightmost candidate and backtrack if it fails.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

using namespace std;

//// simple regex match (internal entry point) ////////////////////////////////////////

bool simple_regex_match( const string & subj, int spos,
			 const string & pat,  int ppos) {
    int original_spos = spos; // in case we must restart match to the right
    int original_ppos = ppos; // in case we must restart match to the right
    char scar = subj[spos];
    char pcar = pat[ppos];
    // first find a starting point where pat[ppos] matches char in subj
    
    while (scar != pcar) {
	++spos;
	if (spos == subj.length()) {
	    return false; // hit end of subject without ever matching.
	    // (note we could stop looking based on not enough characters
	    // in subject to satisfy pattern, but this is complicated by
	    // potential for wildcard in pattern)
	}
	scar = subj[spos];
    }
    
    assert(pat[ppos] == subj[spos]); // i.e., scar == pcar
    assert(scar == subj[spos]);

    // Resume the synchronized traversal of pat and subj,
    // matching as far as possible, and restarting recursively
    // if the '@' (originally unescaped '*') is encountered.
    // Re-matching subj[spos] with pat[spos] simplifies the logic, IMO.
    
    while (true) {
	if (scar != pcar) {
	    if (pcar == '@') {
		return simple_regex_match(subj, ++original_spos,
						pat, ppos + 1);
	    }
	    else {
		// fail - try again with next char to right in subj
		return simple_regex_match(subj, ++original_spos,
						pat, original_ppos);
	    }
	}
	++spos; ++ppos;
	if (ppos == pat.length()) {
	    // exhausted the pattern without a mismatch -> success
	    return true;
	}
	else if (spos == subj.length()) {
	    // ran out of subject before match completed
	    return false;
	}
	scar = subj[spos];
	pcar = pat[ppos];
    }
    assert(false);
}

//// simple regex match (external entry point) ////////////////////////////////////////

bool simple_regex_match(const string & subj, string & pat) {
    /*  Before trying to match, this routine does the following
        preprocessing:
	1. Returns true if the pattern consists of a single '*'
	character.
	2. Removes a leading or trailing unescaped '*' from pattern.
	3. Scans pattern left to right and does the following
	   a. removes escape character ('\') preceding a '*'.
	   b. To help simplify the logic, replaces unescaped '*'s with
	      another character.  Any non-alpha character (printable
	      preferred 8-) is ok ...  how about '@'?  
    */
    if (pat.length() == 1 && pat[0]  == '*') {
	return true;
    }
    if (pat[0] == '*') {
	pat.erase(0, 1); // lop it off
    }

    int pat_last_idx = pat.length() - 1;
    if (pat[pat_last_idx] == '*' &&
	    pat[pat_last_idx - 1] != '\\') {
	pat.erase(pat_last_idx, 1);
    }

    int ppos = pat.length();
    while (--ppos >= 0) {
	if (pat[ppos] == '*') {
	    if (pat[ppos - 1] != '\\') {
		pat[ppos] = '@';
	    }
	    else {
		--ppos;
		pat.erase(ppos, 1);
	    }
	}
    }

    bool ans = simple_regex_match(subj, 0, pat, 0);
    return ans;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
	cout << "usage: " << argv[0] << "<filename>\n";
	return 1;
    }

    ifstream ifs(argv[1]);
    string line;

    while (getline(ifs, line)) {
	unsigned comma_pos = line.find(',');
	string subj = line.substr(0, comma_pos);
	string pat = line.substr(comma_pos + 1, string::npos);
	bool ans = simple_regex_match(subj, pat);
	cout << (ans ? "true" : "false") << endl;
    } // while getline
}
