/*
URI COMPARISON - CodeEval Moderate challenge

CHALLENGE DESCRIPTION:

Determine if two URIs match. For the purpose of this challenge, you
should use a case-sensitive octet-by-octet comparison of the entire
URIs, with these exceptions: 

1. A port that is empty or not given is equivalent to the default port of 80 
2. Comparisons of host names MUST be case-insensitive 
3. Comparisons of scheme names MUST be case-insensitive 
4. Characters are equivalent to their % HEX HEX encodings. (Other than
   typical reserved characters in urls like , / ? : @ & = + $ #)

INPUT SAMPLE:

Your program should accept as its first argument a path to a filename.
Each line in this file contains two urls delimited by a semicolon. E.g.

http://abc.com:80/~smith/home.html;http://ABC.com/%7Esmith/home.html

OUTPUT SAMPLE:

Print out True/False if the URIs match. E.g.

True

*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

bool is_valid_hex_number(const string & h) {
    // MUST be two characters
    return h.size() == 2 && isalnum(h[0]) && isalnum(h[1]);
    
}

void expand_percent_encoding( string & s ) {
    for (unsigned i = 0; i < s.size()-2; ++i) {
        if (s[i] != '%') continue;
        string enc = s.substr(i + 1, 2);
        // probably better to use strtol and friends and check error
        // return
        if (!is_valid_hex_number(enc)) continue;
        istringstream iss(enc);
        unsigned cval;
        iss >> std::hex >> cval;
        s[i] = cval;
        s.erase(i + 1, 2);
    }
}

bool stripped_port( string & s ) {
    // looking at something like <scheme>://foo.bar{:nnn}/...
    // where the port, denoted in braces, is optional.
    unsigned pos = s.find_first_of(':');
    pos = s.find_first_of(':', pos+1);
    if (pos == (unsigned)s.npos) return false;
    // erase from s.pos up to but not including the next '/' (or end of string)
    unsigned slash_pos = s.find_first_of('/', pos+1);
    s.erase(pos, slash_pos - pos);
    return true;
}

void normalize_ports(string & s1, string & s2) {
    // s1 may have compared unequal to s2 b/c one has an explicit port of :80
    // and the other omits a port specifier (thereby defaulting to :80.
    // It should be sufficient to locate a port specifier in either s1 or s2
    // and remove it, then compare for equality.  We are not really 'normalizing',
    // just doing the minimum work;
    
    if (stripped_port(s1)) return;
    stripped_port(s2);  
}

// ensure hostname is lower case
void lwc_scheme_hostname( string & s )
{
    unsigned pos = s.find_first_of(':');
    // What follows position pos one or two slashes, followed by a hostname,
    // optionally followed by a slash and more path info.  The latter should
    // retain its initial case.
    pos++;
    while (s[pos] == '/') pos++;
    pos = s.find_first_of('/', pos);
    if (pos == (unsigned) s.npos) {
        // no slash after hostname - hit end of string;
        pos = s.size();
    }
    
    for (unsigned i = 0; i < pos; ++i) {
        char c = s[i];
        if (c >= 'A' && c <= 'Z') {
            s[i] = c - 'A' + 'a';
        }
    }
}

bool are_equal_URIs( string & s1, string & s2 )
{
#ifdef DEBUG
    cout << "string 1: " << s1 << '\n';
    cout << "string 2: " << s2 << '\n';
#endif
    // comparison to the right of the hostname is case sensitive,
    // so the following is wrong
    // transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
    // transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
    
    lwc_scheme_hostname(s1);
    lwc_scheme_hostname(s2);
    
    expand_percent_encoding(s1);
    expand_percent_encoding(s2);
    
#ifdef DEBUG
    cout << "\nAfter % coding expansion\n";
    cout << "string 1: " << s1 << '\n';
    cout << "string 2: " << s2 << '\n';
#endif

    if (s1 == s2) return true;
    
    // s1 != s2 possibly because of a port specifier mismatch - see called routine
    normalize_ports(s1, s2);
    
    // note:
    //  - we are assuming valid URIs
    //  - we do not handle otherwise equal URIs where only one has a trailing '/'
    //  - we are not handling the case where there is a leading "authority"
    //    phrase before the hostname, e.g., http://joe_blo:pw_usually@foo.bar:80/...
    //    The additional colon is not handled correctly.
    
    return s1 == s2;
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        cout << "usage: " << argv[0] << "<filename>\n";
        return 1;
    }

    ifstream ifs(argv[1]);
    string line;

    while (getline(ifs, line))
    {
        // cout << line << endl;
        unsigned semi_pos = line.find_first_of(';');
        string s1 = line.substr(0, semi_pos);
        string s2 = line.substr(semi_pos + 1);  // munch until end of string
        if (are_equal_URIs(s1, s2)) {
            cout << "True";
        }
        else {
            cout << "False";
        }
        cout << endl;
    } // while getline
}

