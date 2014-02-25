#ifndef DICT_H_INCLUDED
#define DICT_H_INCLUDED

/* 
	Interface for a dictionary.

	Bugs:
		How to switch out implementations that rely on different underlying tech
		(e.g., std::set vs. rolling our own trie) without this file having to
		know about it?  If we use std::unordered_set we don't need dictnode.
		Do we need another include that has the shared stuff in it, and then
		the user has to worry about including dicttrie.h vs. dictset.h?

		The usage model I have in mind is probably broken anyway, because
		if both implementations are in a library, under my scenario there
		would be name clashes on the entry points.

		Can/should this be a const set? Elements in sets are const anyway.
*/

#ifdef DICT_TRIE

#include <vector>

class dictnode {
	bool ends_word;
	vector<dictnode *> children;
};

#else // (not) DICT_TRIE

#include <unordered_set> // faster than plain vanilla set

#endif // (not) DICT_TRIE

#include <string>

class Dictionary {
public:
	bool lookup(std::string &);
	void enter(std::string &);
private:

#ifdef DICT_TRIE
#else // (not) DICT_TRIE

	std::unordered_set<std::string> dictset;

#endif // (not) DICT_TRIE

};

#endif // DICT_H_INCLUDED
