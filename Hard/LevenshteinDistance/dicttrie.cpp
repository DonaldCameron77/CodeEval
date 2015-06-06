
// dicttrie.cpp
//
// implementation of class Dictionary - trie approach

// Unfortunately it has a bigger memory footprint than the
// unordered_set implementation, most likely because every
// dictnode has a 26-element vector of pointers (representing
// a-z.  Would try a linked list or other less wasteful
// approach instead.  See the Wikipedia trie entry for starters.

#include <string>

#include <iostream>  // debugging code and error exit

#include "dict.h"

using namespace std;

Dictionary::Dictionary() {
    root = new Dictnode();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
    Dictionary::lookup

    Theory of Operation:
        Iterations are driven by walking down the string s and following
        along through the trie data structure.  At each node, see if
        children[current_letter] is null.  If it is, report failure;
        otherwise, if this is the last letter in s and
        cur_node->ends_word is true, report success, else
        advance to the next letter and next node.

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

bool Dictionary::lookup(const string & s)
{
    // DEBUG
    // cout << "Dictionary::lookup ... trying " << s << endl;

    Dictnode * cur_node = this->root; // note root does not represent any letter!!!!!!

    for (unsigned i = 0; i < s.length(); ++i)
    {
        char cur_letter_index = s[i] - 'a';

        // as in the enter case, we don't really need the extra
        // variable, but it makes things clearer for a first draft
        Dictnode * next_node = cur_node->children[cur_letter_index];
        if (next_node == NULL) {
            // we have a letter to match, but there is no corresponding
            // letter in the current prefix the dictionary has
            return false;
        }

        // current letter matched in dictionary
        if (i == s.length() - 1) {
            return next_node->ends_word ? true : false;
        }

        // advance
        cur_node = next_node;
    }
    // can we fall off the end of the string
    // without hitting one of these cases? No.
    cerr << "Dictionary::lookup : unexpected end of loop\n";
    throw;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
    Dictionary::enter

    Theory of operation:
        Walking the string drives the insertion process.-
        There are 2 cases:
        1. We arrive at a Dictnode and the current letter
           ends the word.  Set cur_node->ends_word to true and exit.
        2. We arrive at a Dictnode and the current letter does
           not end the word.
           if cur_node->children[cur_letter] is null
                set cur_node->children[cur_letter] to new Dictnode
           advance by setting cur_letter to next letter in string,
           and set cur_node to cur_node->children->cur_letter

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void Dictionary::enter( const string & s )
{
    Dictnode * cur_node = this->root;
    // Note root does not represent any letter!!!!!!

    // dunno if we need the second pointer next_node but
    // it seems clearer to develop with itj

    for (unsigned i = 0; i < s.length(); ++i)
    {
        char cur_letter_index = s[i] - 'a';

        Dictnode * next_node = cur_node->children[cur_letter_index];
        // IDK if we need the second pointer next_node,
        // but it seems clearer to develop with it

        if (next_node == NULL) {
            next_node = cur_node->children[cur_letter_index] = new Dictnode();
        }

        cur_node = next_node;

        if (i == s.length() - 1) {
            cur_node->ends_word = true;
            return;
        }

        /*
        if (cur_node->children[cur_letter_index] == NULL) {
            cur_node->children[cur_letter_index] = new Dictnode();
        }

        cur_node = cur_node->children[cur_letter_index];
        */
    }
}

// EOF

