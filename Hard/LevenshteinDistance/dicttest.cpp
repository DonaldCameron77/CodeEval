#include <string>
#include <iostream>

using namespace std;

#include "dict.h"

int main() {
    string a[] = { "red", "green", "blue" };
    Dictionary tbl;
    for (int i = 0; i < 3; ++i) {
        tbl.insert(a[i]);
    }

    bool found = tbl.lookup(a[1]);
    if (found)
        cout << "found it!";
    else
        cout << "entered string not found 8-(";
    cout << endl;
}
