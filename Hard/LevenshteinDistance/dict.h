#ifndef DICT_H_INCLUDED
#define DICT_H_INCLUDED

/* 
    Interface for a dictionary.

    Bugs: How to switch out implementations that rely on different
        underlying tech (e.g., std::set vs. rolling our own trie) without
        this file having to know about it?  If we use std::unordered_set we
        don't need Dictnode.  Do we need another include that has the shared
        stuff in it, and then the user has to worry about including
        dicttrie.h vs. dictset.h?

        The usage model I have in mind is probably broken anyway,
        because if both implementations are in a library, under my
        scenario there would be name clashes on the entry points.

        Can/should this be a const set? Elements in sets are const anyway.
*/

#ifdef DICT_TRIE

#include <vector>

/*
    Basic trie data structure.  At each node, we must be prepared
    to store and/or find any of 26 letters.  They're not all equally
    likely, of course, but for the moment we'll use a vector of 26.
    Eventually we will wind up allowing for a sparse set of characters ranging
    from 'a' to 'z' ... but not yet.
*/

class Dictnode
{
private:
    friend class Dictionary;

    bool ends_word;
    std::vector<Dictnode *> children;

    Dictnode() : ends_word(false), children(26, NULL) {}
};

#else // (not) DICT_TRIE

#include <unordered_set> // faster than plain vanilla set

#endif // (not) DICT_TRIE

#include <string>

class Dictionary {
public:
    bool lookup( const std::string & );
    void enter(const std::string & );
#ifdef DICT_TRIE
    Dictionary();
#endif // DICT_TRIE
private:
#ifdef DICT_TRIE
    Dictnode * root;

#else // (not) DICT_TRIE

    std::unordered_set<std::string> dictset;

#endif // (not) DICT_TRIE

};

#endif // DICT_H_INCLUDED
