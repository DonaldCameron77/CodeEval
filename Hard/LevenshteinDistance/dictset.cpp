// Implementation for Dictionary class
//
// This version uses std::unordered_set for its underlying implementation.
// Basic a wrapper to facilitate alternate implementations. See also dicttrie.cpp
//
// 
//

#include <string>

#include "dict.h"

bool Dictionary::lookup(std::string & s) {
    // std::unordered_set<std::string>::const_iterator is = this.find(s);
    const auto is = dictset.find(s);
    return is == dictset.end() ? false : true;
}

void Dictionary::enter(std::string & s) {
    dictset.insert(s);
}

