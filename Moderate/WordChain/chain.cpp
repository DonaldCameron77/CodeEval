/*
WORD CHAIN - CodeEval Moderate challenge
CHALLENGE DESCRIPTION:

In this challenge we suggest you to play in the known game "Word chain"
in which players come up with words that begin with the letter that the
previous word ended with. The challenge is to determine the maximum
length of a chain that can be created from a list of words.

INPUT SAMPLE:

Your program should accept as its first argument a path to a filename.
Each line in this file contains a list of words separated by comma. E.g.

soup,sugar,peas,rice
ljhqi,nrtxgiu,jdtphez,wosqm
cjz,tojiv,sgxf,awonm,fcv

OUTPUT SAMPLE:

Print out the length of the longest chain, print out "None" if there is no chain . E.g.

4
None
2

Constraints:

The length of a list of words is in range [4, 35] A word in a list of
words is represented by a random lowercase ascii string with the length
of [3, 7] letters.  There is no repeating words in a list of words.
*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>    // replace
#include <map>          // multimap
#include <utility>      // make_pair

using namespace std;

struct sdescr {
    string s;
    bool in_use;
    sdescr(string t) : s(t), in_use(false) {}
};

unsigned chain_helper( 
    multimap <char, sdescr> & strmap, char link, unsigned len_so_far)
{
    pair <multimap<char, sdescr>::iterator, multimap<char, sdescr>::iterator> ret;
    ret = strmap.equal_range(link);
    unsigned max_chain = len_so_far;
    for (auto it = ret.first; it != ret.second; ++it) {
        sdescr & sd = it->second;
        if (sd.in_use) continue;
        else sd.in_use = true;
        char nxt_link = sd.s[sd.s.length()-1];
        unsigned cur_chain = chain_helper(strmap, nxt_link, len_so_far + 1);
        sd.in_use = false;
        if (cur_chain > max_chain) max_chain = cur_chain;
    } 
    return max_chain;  
}

unsigned find_longest_chain( multimap <char, sdescr> & strmap ) {
    unsigned max_chain = 0;
    for (auto it = strmap.begin(); it != strmap.end(); ++it) {
        sdescr & sd = it->second;
        char link = sd.s[sd.s.length()-1];
        sd.in_use = true;
        unsigned cur_chain = chain_helper(strmap, link, 1);
        sd.in_use = false;
        if (cur_chain > max_chain) max_chain = cur_chain;
    }
    return max_chain == 1 ? 0 : max_chain;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "usage: " << argv[0] << "<filename>\n";
        return 1;
    }

    ifstream ifs(argv[1]);
    string line;
    multimap < char, sdescr> strmap;

    while (getline(ifs, line))
    {
        replace(line.begin(), line.end(), ',', ' ');
        strmap.clear();
        istringstream iss(line);
        string s;
        while (iss >> s) {
                // cout << s << " "; // output line will have trailing ' '
            strmap.insert(make_pair(s[0], s));
        }
        // cout << endl;
        // now print what we have
        // for (auto it = strmap.begin(); it != strmap.end(); ++it) {
                // cout << it->second.s << " ";
        // }
        // cout << endl;
        
        unsigned len = find_longest_chain(strmap);
        if (len) cout << len;
        else cout << "None";
        cout << endl;

    } // while getline

}
