/* DA VYNCY - CodeEval Hard challenge

CHALLENGE DESCRIPTION:

You were reading The Da Vyncy Code, the translation of a famous murder
mystery novel into Python. The Code is finally revealed on the last
page. You had reached the second to last page of the novel, and then you
went to take a bathroom break. 

While you were in the bathroom, the Illuminati snuck into your room and
shredded the last page of your book. You had 9 backup copies of the book
just in case of an attack like this, but the Illuminati shredded the
last page from each of the those books, too. Then they propped up a fan,
aimed it at the remains, and turned it on at high-speed. 

The last page of your book is now in tatters. 

However, there are many text fragments floating in the air. You enlist
an undergraduate student for a 'summer research project' of typing up
these fragments into a file. Your mission: reassemble the last page of
your book. 

Problem Description 
============= 

(adapted from a problem by Julie Zelenski) 

Write a program that, given a set of fragments (ASCII strings), uses the
following method (or a method producing identical output) to reassemble
the document from which they came: 

At each step, your program searches the collection of fragments. It
should find the pair of fragments with the maximal overlap match and
merge those two fragments. This operation should decrease the total
number of fragments by one. If there is more than one pair of fragments
with a maximal overlap, you may break the tie in an arbitrary
fashion.Fragments must overlap at their start or end. For example:

- "ABCDEF" and "DEFG" overlap with overlap length 3
- "ABCDEF" and "XYZABC" overlap with overlap length 3
- "ABCDEF" and "BCDE" overlap with overlap length 4
- "ABCDEF" and "XCDEZ" do *not* overlap (they have matching characters
  in the middle, but the overlap does not extend to the end of either
string).

Fear not - any test inputs given to you will satisfy the property that
the tie-breaking order will not change the result, as long as you only
ever merge maximally-overlapping fragments. Bonus points if you can come
up with an input for which this property does not hold (ie, there exists
more than 1 different final reconstruction, depending on the order in
which different maximal-overlap merges are performed) -- if you find
such a case, submit it in the comments to your code! 

All characters must match exactly in a sequence (case-sensitive). Assume
that your undergraduate has provided you with clean data (i.e., there
are no typos).

INPUT SAMPLE:

Your program should accept as its first argument a path to a filename.
Each line in this file represents a test case. Each line contains
fragments separated by a semicolon, which your assistant has
painstakingly transcribed from the shreds left by the Illuminati. You
may assume that every fragment has length at least 2 and at most 1022
(excluding the trailing newline, which should *not* be considered part
of the fragment). E.g. Here are two test cases.

O draconia;conian devil! Oh la;h lame sa;saint!

m quaerat voluptatem.;pora incidunt ut labore et d;, consectetur,
adipisci velit;olore magnam aliqua;idunt ut labore et dolore
magn;uptatem.;i dolorem ipsum qu;iquam quaerat vol;psum quia dolor sit
amet, consectetur, a;ia dolor sit amet, conse;squam est, qui do;Neque
porro quisquam est, qu;aerat voluptatem.;m eius modi tem;Neque porro
qui;, sed quia non numquam ei;lorem ipsum quia dolor sit amet;ctetur,
adipisci velit, sed quia non numq;unt ut labore et dolore magnam aliquam
qu;dipisci velit, sed quia non numqua;us modi tempora incid;Neque porro
quisquam est, qui dolorem i;uam eius modi tem;pora inc;am al
OUTPUT SAMPLE:

Print out the original document, reassembled. E.g.

O draconian devil! Oh lame saint!

Neque porro quisquam est, qui dolorem ipsum quia dolor sit amet,
consectetur, adipisci velit, sed quia non numquam eius modi tempora
incidunt ut labore et dolore magnam aliquam quaerat voluptatem.

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Overlap { // describes current maximum overlap found
    unsigned index_1, index_2; // indices into string vector
    unsigned size;   // amount of overlap
    enum { full, partial } overlap_type; 
    unsigned pos1, pos2;
    /*
        Here is the protocol for usage of these data members.  The
        objective is to provide enough info to the merge routine
        that it can commence merging the two strings w/o any
        re-analysis ...

        index_1 - svec[index_1] is one of the strings described
        index_2 - svec[index_2] is the other string described.
            svec[index_1] is at least as long as the the other string.
        size - number of characters of overlap.  IMO this is derivable
            from other info, but the analyzer should have this info
            so we record it anyway.
        overlap_type - full means svec[index_2] is fully overlapped
            by svec[index_1], and can simply be thrown away at
            merge time.
        pos1, pos2.  Used only for partial overlaps. If the left
        end of svec[index_2] overlaps the right end of svec[index_1],
        then pos2 will be zero, and svec[index_1][pos1] will be the
        leftmost character of svec[index_1] involved in the overlap.
        The converse is true if the right end of svec[index_2] overlaps
        the left end of svec[index_1].
    */

public:
    void analyze_overlap( const vector<string> & svec, size_t xs, size_t xt );
    Overlap() : size(0) {} // indicates no overlap set - initial condition
    void merge_strings( vector<string> & svec );
};

void Overlap::analyze_overlap(const vector<string> & svec, size_t xs, size_t xt) {
    if (svec[xs].size() < svec[xt].size()) {
        swap(xs, xt);
    }
    const string & s = svec[xs]; // guaranteed to be no shorter than t
    const string & t = svec[xt];
    
    // t completely matches substring of s (all of t, could be all of s)
    if (s.find(t) != string::npos) {
        if (t.size() > size) {
            size = t.size();
            index_1 = xs;
            index_2 = xt;
            overlap_type = full;
        }
        return;
    }

    size_t ssize = s.size();
    size_t tsize = t.size();

    // for each position in s, see if t can overlap it.
    // If so, and the amount of overlap is larger that
    // we've see before, update the overlap data

    // first look at overlapping right end of s with left end of t
    for (int len = tsize - 1; len > 0; --len) {
        if (len <= (int)size) {
            break; // no more chances for a new max here
        }
        // try to match s[ssize-len .. ssize-1] with t[0 .. len-1]
        if ( s.substr(ssize - len).compare( t.substr(0, len) ) == 0)
        {
            // if we have a match, it's guaranteed to be the biggest so far
            index_1 = xs;
            index_2 = xt;
            size = len;
            overlap_type = partial;
            pos1 = ssize - len;
            pos2 = 0;
        }
    }

    // now analyze overlapping left end of s with right end of t
    for (int len = tsize - 1; len > 0; --len) {
        if (len <= (int)size) {
            break; // no more chances for a new max here
        }
        // try to match s[ssize-len .. ssize-1] with t[0 .. len-1]
        // try to match s[0 .. len-1] with t[tsize-len .. tsize-1]

        if ( s.substr(0, len).compare( t.substr(tsize - len) ) == 0)
        {
            // if we have a match, it's guaranteed to be the biggest so far
            index_1 = xs;
            index_2 = xt;
            size = len;
            overlap_type = partial;
            pos1 = 0;
            pos2 = tsize - len;
        }
    }
}

void Overlap::merge_strings( vector<string> & svec ) {
    // result of merge always writes over the rightmost of the subject strings
    size_t target_ix = index_1 > index_2 ? index_1 : index_2;
    if (overlap_type == full) {
        // bit of a kludge.  We're "thowing away" svec[index_2] as
        // it is the shorter string and is fully overlapped by the
        // longer svec[index_1].  But we want the result string 
        // to be "to the right" in svec, i.e., have the higher index
        if (index_1 != target_ix) {
            svec[target_ix] = svec[index_1];
        }
        return;
    }
    else
    {   // partial overlap
        string & s = svec[index_1];
        string & t = svec[index_2];
        if (pos2 == 0) { 
            svec[target_ix] = s.substr(0, pos1) + t;
        }
        else {
            svec[target_ix] = t.substr(0, pos2) + s;
        }
    }
}

void split( string & line, vector<string> & svec, char delim) {
    size_t dpos = line.find(delim);
    while (dpos != line.npos) {
        string cur = line.substr(0, dpos);
        svec.push_back(cur); 
        line.erase(0, dpos+1);
        dpos = line.find(delim);
    }
    // the final substring remaining in 'line' is terminated by
    // '\n' or null, so we'll arrive here and need to push it back
    svec.push_back(line);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "usage: " << argv[0] << "<filename>\n";
        return 1;
    }
    ifstream ifs(argv[1]);
    string line;
    while (getline(ifs, line)) {
        vector<string> svec;
        // need to split line based on ';' delimiter or eof
        split(line, svec, ';');

        // Merging the "leftmost" element of svec with the remaining
        // element with which it has the biggest overlap.  Ignores
        // the possibility of bigger overlaps among the remaining
        // elements, but this doesn't seem to matter(?). I haven't
        // been able to compose a counterexample.
        for (size_t i = 0; i < svec.size() - 1; ++i) {
            Overlap max_overlap;
            for (size_t j = i + 1; j < svec.size(); ++j) {
                max_overlap.analyze_overlap(svec, i, j);
            }
            max_overlap.merge_strings(svec);
        }
        // only one element left in svec now
        cout << svec.back() << endl;
    }
}

// EOF
