/*
    LEVENSHTEIN DISTANCE - CodeEval Hard challenge
    CHALLENGE DESCRIPTION:

    Two words are friends if they have a Levenshtein distance of 1 (For
    details see Levenshtein distance on Wikipedia). That is, you can
    add, remove, or substitute exactly one letter in word X to create
    word Y. A word’s social network consists of all of its friends, plus
    all of their friends, and all of their friends’ friends, and so on.
    Write a program to tell us how big the social network for the given
    word is, using our word list.

    INPUT SAMPLE:

    The first argument will be a path to a filename, containing words,
    and the word list to search in. The first N lines of the file will
    contain test cases, they will be terminated by string 'END OF
    INPUT'. After that there will be a list of words one per line. E.g

    recursiveness
    elastic
    macrographies
    END OF INPUT
    aa
    aahed
    aahs
    aalii
    ...
    ...
    zymoses
    zymosimeters

    OUTPUT SAMPLE:

    For each test case print out how big the social network for the word is. In sample
    the social network for the word 'elastic' is 3 and for the word 'recursiveness' is 1.
    E.g.

    1
    3
    1

    Constraints: 
    Number of test cases N in range(15, 30) 
    The word list always will be the same, and its length will be around 10000 words 
*/

// Notes =========================================================================
/*  Computing the Levenshtein Distance between two words doesn't use a dictionary.
    This problem does, and it is provided in the input.  Also, we are not going
    for a minimum distance between two words, but merely using the Levenshtein
    transformations one at a time, starting with the input word and then going
    into the dictionary and seeing how many words we can reach, directly or
    indirectly.
    
    We can't dump the input file at CodeEval in the usual manner - it's too big.
    
    Approach: we're going to use a trie as the underlying data structure for the
    dictionary.  Operations include insert and lookup.
    
    So if an input word is "foo," say, we'll successively form
    
        [a-eg-z]oo, f[a-np-z]o, fo[a-np-z]o         // substitutions
        fo, fo (duplicate - can we prune?), and oo  // deletions
        [a-z]foo, f[a-z]oo, fo[a-z]o, foo[a-z]      // insertions
        
    and see if they are in the dictionary.  If a word is found, we increment
    friend_count and start over with the word we found. We need to be careful
    not to find words again that we already found for this input.
*/

#include <iostream>
#include <fstream>

#include <vector>           // candidates
#include <queue>            // friend list
#include <unordered_set>    // members of a candidate's social graph found so far

#include "dict.h"

using namespace std;

void get_candidates(vector<string> & cand, ifstream & ifs) {
    string line;
    while (getline(ifs, line)) {
        if (line == "END OF INPUT") return;
        cand.push_back(line);
#ifdef DEBUG
        cout << "Entered candidate \"" << line << "\"\n";
#endif // DEBUG
    }
    cout << "Error - input file format incorrect" << endl;
}

void fill_dictionary(Dictionary & dict, ifstream & ifs) {
    string line;
    while (getline(ifs, line)) {
        dict.enter(line);
#ifdef DEBUG
        cout << "made dictionary entry for \"" << line << "\"\n";
#endif // DEBUG
    }
}

// compute the social graph of str with respect to dict.  See above for details
unsigned get_graph(const string & str, Dictionary & dict)
{
    // Using a single Levenshtein transformation (add, remove, or substitute one letter),
    // compute the size of the 'social graph' of str.
    
    // When we find a friend of the candidate string, we add it to the candidate list.
    // We also add it to the found set, because we don't want to count it again if
    // we somehow stumble upon it a subsequent time. (Test if the latter is needed).
    
    // if we never deleted from members, we could just use one list, but
    // it would have to support fast lookup, avoidance of dups when inserting,
    // and a "next element" method
    
    queue<string> members; // str and its friends
    unordered_set<string> found; // to avoid re-finding and retrying a member
    
    found.insert(str);
    members.push(str);
    
    while (!members.empty())
    {
        const string cur_str = members.front();
        members.pop();
        
        // character removal
        for (unsigned i = 0; i < cur_str.length(); ++i) {
            string tmp = cur_str;
            tmp.erase(i, 1);
            if (found.find(tmp) == found.end() && dict.lookup(tmp)) {
                found.insert(tmp);
                members.push(tmp);
            }
        }
        
        // character replacement
        for (unsigned i = 0; i < cur_str.length(); ++i) {
            string tmp = cur_str;
            for (char c = 'a'; c <= 'z'; ++c) {
                if (c == cur_str[i]) continue; // don't replace original char with itself
                tmp[i] = c;
                if (found.find(tmp) == found.end() && dict.lookup(tmp)) {
                    found.insert(tmp);
                    members.push(tmp);
                }
            }
        } 
        
        // character insertion
        for (unsigned i = 0; i < cur_str.length(); ++i) {
            string tmp = cur_str;
            tmp.insert(i, 1, ' '); // placeholder for the following insertions
            for (char c = 'a'; c <= 'z'; ++c) {
                tmp[i] = c;
                if (found.find(tmp) == found.end() && dict.lookup(tmp)) {
                    found.insert(tmp);
                    members.push(tmp);
                }
            }
        } 
        // Above does not append after last char.
        // Note append modifies its argument.  We could recode this
        // to avoid having to copy into tmp every time, but it's only 26 copies.
        for (char c = 'a'; c <= 'z'; ++c) {
            string tmp = cur_str;
            tmp.append(1, c);
            if (found.find(tmp) == found.end() && dict.lookup(tmp)) {
                found.insert(tmp);
                members.push(tmp);
            }
        }
         
    } // while
    return found.size(); // note original string is included in count
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "usage: " << argv[0] << "<filename>\n";
        return 1;
    }

    ifstream ifs(argv[1]);
    
    vector<string> cand;
    get_candidates(cand, ifs);
    
    Dictionary dict;
    fill_dictionary(dict, ifs);
    
    for (auto it = cand.cbegin(); it != cand.cend(); ++it) {
        unsigned friend_ct = get_graph(*it, dict);
        cout << friend_ct << endl;
    }
}

// EOF
