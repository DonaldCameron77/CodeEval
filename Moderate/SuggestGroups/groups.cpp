/* SUGGEST GROUPS - CodeEval Moderate challenge

CHALLENGE DESCRIPTION:

You may have noticed that a new feature was added to our web site – user
groups. So, this challenge is about joining groups.

You are given a list of users of a social network, friends of each user,
and groups the user participates in.

To help users find the most interesting groups, we suggest them joining
the groups where ≥50% of their friends participate.

Your task is to write a program which finds a list of suggested groups
for each user.

INPUT SAMPLE:

The first argument is a file that contains the information about each
user, one user per line. The line is delimited by colon ‘:’ into three
parts: user name, list of friends, and list of groups. The items in each
part are delimited by comma ‘,’.

For example:

Amira:Isaura,Lizzie,Madalyn,Margarito,Shakira,Un:Driving,Mineral collecting
Elliot:Isaura,Madalyn,Margarito,Shakira:Juggling,Mineral collecting
Isaura:Amira,Elliot,Lizzie,Margarito,Verla,Wilford:Juggling
Lizzie:Amira,Isaura,Verla:Driving,Mineral collecting,Rugby
Madalyn:Amira,Elliot,Margarito,Verla:Driving,Mineral collecting,Rugby
Margarito:Amira,Elliot,Isaura,Madalyn,Un,Verla:Mineral collecting
Shakira:Amira,Elliot,Verla,Wilford:Mineral collecting
Un:Amira,Margarito,Wilford:
Verla:Isaura,Lizzie,Madalyn,Margarito,Shakira:Driving,Juggling,Mineral collecting
Wilford:Isaura,Shakira,Un:Driving

OUTPUT SAMPLE:

Print to stdout the list of suggested groups for each user. The list of
users and the list of groups for each user must be sorted
alphabetically.

For example:

Isaura:Driving,Mineral collecting
Lizzie:Juggling
Madalyn:Juggling
Margarito:Driving,Juggling
Shakira:Driving,Juggling
Un:Driving,Mineral collecting

CONSTRAINTS:

- Number of users in input data is 200.
- Number of different groups in input data is 15.
- There can be users that do not participate in any group.
- Friendship is mutual (if user A is a friend with user B,
  then user B is a friend with user A).
================================================================= */

#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

// This could have been done with an array of class objects indexed by
// user.  Each object would have a vector of friends and another
// of groups.  The present method instead mirrors the approach taken
// with Ruby, and serves as an exercise in using the STL hash (map)
// container.
//
// It might be good to recode the Ruby version using the
// array-of-objects approach, to exercise the Ruby class facilities 8-)
//
// Apparently you would have a hash whose keys are users, and whose
// value is a class object, with friends and groups vectors as members.

typedef map<string, vector<string> > hashed_list;

// Adapted from Evan Teran at
//     http://stackoverflow.com/questions/236129/how-to-split-a-string-in-c    
// Changed to be a void function
void split( const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

void make_map_entry(
    hashed_list & the_map, const string & key, const string & the_list)
{
    // turn list into a vector 'elems' ( in Ruby, split(',') )
    vector<string> elems;
    split(the_list, ',', elems); 

    // make new entry in the map from the pair (key, vec)
    the_map.insert(make_pair(key, elems));
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    ifstream ifs(argv[1]);
    string line;

    hashed_list friends_map, groups_map;

    while (getline(ifs, line)) {
        // DEBUG: cout << line << endl;
        // First, split input line into user, friends, and groups.
        // We can't simply replace colons by blanks and use isstringstream
        // b/c group names can contain blanks (e.g, "Mineral collecting")
        unsigned colonpos_1 = line.find_first_of(':');
        string user = line.substr(0, colonpos_1);
        unsigned colonpos_2 = line.find_first_of(':', colonpos_1 + 1);
        string friends = line.substr(colonpos_1 + 1,
                                        colonpos_2 - colonpos_1 - 1);
        string groups = line.substr(colonpos_2 + 1, string::npos);
        // string substr (size_t pos = 0, size_t len = npos) const;
        // DEBUG: cout << user << ':' << friends << ':' << groups << endl;

        make_map_entry(friends_map, user, friends);
        make_map_entry(groups_map, user, groups);
    } // while getline

    // Keep an initially empty list (map<string,int> recs) of each of u's
    // friends' groups that is not also one of u's groups initially.
    // Count the number of times each group appears.  When done with
    // the friends' groups, see if any groups appear among half or more of
    // u's friends.  If any, then print a line of output with
    // u:<recommended groups>

    for (auto it = friends_map.begin(); it != friends_map.end(); ++it)
    {
        string u = it->first;                       // current user name
        const vector<string> & flist = it->second;  // const reference
        map<string,int> recs;                      // raw recommendations list
        for (unsigned ff = 0; ff < flist.size(); ++ff)  // iterate over friend vector
        {
            string f = flist[ff];                   // current friend
            vector<string> & glist = groups_map[f]; // friend f's groups
            for (unsigned gg = 0; gg < glist.size(); ++gg)
            {
                string g = glist[gg];               // current group of friend f
                // Does u already have this group?
                vector<string> uglist = groups_map[u];   // u's groups
                vector<string>::iterator gt = find(uglist.begin(), uglist.end(), g);
                if (gt == uglist.end()) { // if g isn't in u's groups
                    recs[g] += 1;   // if nonexistent, will zero-initialize
                }
            } // end gg
        } // end ff
        int threshold =(flist.size() + 1) / 2;  // minimum matches to recommend group
        vector<string> rec_vec;                 // we'll copy the recommended groups from
                                                // the hash 'recs' into
                                                // this vector for ease
                                                // of sorting
        int rec_count = 0;
        for (auto rt = recs.begin(); rt != recs.end(); ++rt) {
            if (rt->second >= threshold) {
                ++rec_count;
            }
        }
        if (rec_count > 0) {
            cout << u << ':';
            bool first = true;
            for (auto rt = recs.begin(); rt != recs.end(); ++rt) {
                if (rt->second >= threshold) {
                    if (first) {
                        first = false;
                    }
                    else {
                        cout << ',';
                    }
                    cout << rt->first;
                }
            }
            cout << endl;
        }
    } // for it
}

// EOF
