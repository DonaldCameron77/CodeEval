// Poker Hands - CodeEval Hard challenge

/* Description from CodeEval site:
CHALLENGE DESCRIPTION:

In the card game poker, a hand consists of five cards and are ranked,
from lowest to highest, in the following way:

High Card: Highest value card.
One Pair: Two cards of the same value.
Two Pairs: Two different pairs.
Three of a Kind: Three cards of the same value.
Straight: All cards are consecutive values.
Flush: All cards of the same suit.
Full House: Three of a kind and a pair.
Four of a Kind: Four cards of the same value.
Straight Flush: All cards are consecutive values of same suit.
Royal Flush: Ten, Jack, Queen, King, Ace, in same suit.
The cards are valued in the order:
2, 3, 4, 5, 6, 7, 8, 9, Ten, Jack, Queen, King, Ace.

If two players have the same ranked hands then the rank made up of the
highest value wins; for example, a pair of eights beats a pair of fives.
But if two ranks tie, for example, both players have a pair of queens,
then highest cards in each hand are compared; if the highest cards tie
then the next highest cards are compared, and so on.

INPUT SAMPLE:

Your program should accept as its first argument a path to a filename.
Each line in this file contains 2 hands (left and right). Cards and
hands are separated by space. E.g.

6D 7H AH 7S QC 6H 2D TD JD AS
JH 5D 7H TC JS JD JC TS 5S 7S
2H 8C AD TH 6H QD KD 9H 6S 6C
JS JH 4H 2C 9H QH KC 9D 4D 3S
TC 7H KH 4H JC 7D 9S 3H QS 7S
OUTPUT SAMPLE:

Print out the name of the winning hand or "none" in case the hands are equal. E.g.

left
none
right
left
right
*/

/* Bugs:
		Ace-low not handled (for straights and straight_flushes).
		Royal flush interpreted as Ace-hi straight flush.
*/

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// The description doesn't allow for ace-low.
// Also, a royal flush is just an Ace-high straight flush - no
// special handling needed.

// Spelling 'flush' as 'phlush' needed to avoid name conflict with
// 'flush' in STL. Disambiguating with 'ranktype::flush' does not
// work with all compilers.
enum ranktype { uninit, high_card, one_pair, two_pair, trips, straight,
		phlush, full_house, quad, straight_flush };

class card {
    int _rank; // 2..13
    char _suit;
public:
    card( char r, char s ); 
    card() {} // default ctor for initializing handtype::_card 	
    int rank() const { return _rank; }
    char suit() const { return _suit; }
};

card::card( char r, char s )
{
    static const string ranks = "23456789TJQKA";
    _rank = ranks.find(r)+2;
    _suit = s;
}

class handtype
{
    int _insert_pt; // [0..5], 5 implying hand has max no. of cards
    card _card[5]; // this is the actual set of 5 cards
    ranktype _rank;
    int _high;
    void _sort();
    void _compute_rank(); // sets rank and also sorts cards in hand array
    void _do_sort(const int, const int);
    void _do_swap(const int, const int);
    void reorder_two_pair(const int);
    bool _pair_check(int);
    // the following rank-computing functions are designed to be called
    // in the given order.  E.g., _one_pair does not check if two pairs
    // are present
    bool _straight_flush();
    bool _quad();
    bool _full_house();
    bool _flush();
    bool _straight();
    bool _trips();
    bool _two_pair();
    bool _one_pair();
public:
    handtype() { _insert_pt = 0; _rank = uninit; _high = 0; }
    void add_card( const card & c );
    card getcard(int i) const { return _card[i]; }
    ranktype rank() { if (_rank == uninit) _compute_rank(); return _rank; }
    ranktype getrank() const { return _rank; }
    int high() const { return _high; }
};

void handtype::_do_swap(int i, int j) {
    card ctmp = _card[i];
    _card[i] = _card[j];
    _card[j] = ctmp;
}

// It would have been nicer to use vector and pair to get sort, swap 4 free
// Bubble sort is fine for 5 elements 8-)
void handtype::_do_sort(int start, int end) {
    bool changed;
#ifdef DEBUG2
    cout << "do_sort: start = " << start << ", end = " << end << endl;
#endif
    do {
        changed = false;
        for (int i = start; i < end; i++) {
#ifdef DEBUG2
            cout << "do_sort: i = " << i << ", rank[i] == " << _card[i].rank()
                    << ", rank[i+1] == " << _card[i+1].rank() << endl;
#endif
          if (_card[i].rank() < _card[i+1].rank()) {
                _do_swap(i, i+1);
                changed = true;
            }
        } // for
    } while (changed);
}

// hand evaluator functions assume the cards are already sorted
// Note: not required, but Ace-low not handled - see _straight
bool handtype::_straight_flush() {
    for (int i = 1; i < 5; i ++) {
        if (_card[i].suit() != _card[0].suit()) {
            return false;
        }
    }
    for (int i = 0; i < 4; i++) {
        if (_card[i].rank() != _card[i+1].rank()+1) {
            return false;
        }
    }
    _rank = straight_flush;
    _high = _card[0].rank();
    return true;
}

bool handtype::_quad() {
    // for a sorted quad hand, the middle three cards must be equal
    if (_card[1].rank() != _card[2].rank() ||
            _card[1].rank() != _card[3].rank())
        return false;
    
    if (_card[0].rank() == _card[1].rank() ||
             _card[3].rank() == _card[4].rank()) {
        _rank = quad;
        _high = _card[1].rank();
        return true;
    }
    return false;
}

bool handtype::_full_house() {
    if (_card[0].rank() == _card[1].rank() &&
            _card[1].rank() == _card[2].rank() &&
            _card[3].rank() == _card[4].rank()) {
        _rank = full_house;
        _high = _card[0].rank();
        return true;
    }
    else if (_card[0].rank() == _card[1].rank() &&
                _card[2].rank() == _card[3].rank() &&
                _card[3].rank() == _card[4].rank()) {
        _rank = full_house;
        _high = _card[4].rank();
        return true;
    }
    return false;
}	

bool handtype::_flush() {
    for (int i = 1; i < 5; i ++) {
        if (_card[i].suit() != _card[0].suit()) {
            return false;
        }
    }
    _rank = phlush;
    _high = _card[0].rank();
    return true;
}

// To gracefully handle Ace low, check if card[0] is 14 and
// if so, give it special handling
bool handtype::_straight() {
    for (int i = 0; i < 4; i++) {
        if (_card[i].rank() != _card[i+1].rank()+1) {
            return false;
        }
    }
    
    _rank = straight;
    _high = _card[0].rank();
    return true;
}

bool handtype::_trips() {
    if ((_card[0].rank() == _card[1].rank() &&
             _card[1].rank() == _card[2].rank()) ||
            (_card[1].rank() == _card[2].rank() &&
             _card[2].rank() == _card[3].rank())	||
            (_card[2].rank() == _card[3].rank() &&
            _card[3].rank() == _card[4].rank())) {
        _rank = trips;
        _high = _card[2].rank();
        return true;
    }
    return false;
}

// Given two-pair hand which is sorted by card rank.
// Re-sort it as highest pair, lower pair, sidecard.
void handtype::reorder_two_pair( const int sidecard_pos ) {
    if (sidecard_pos == 0) {
        _do_swap(0, 2);
        _do_swap(2, 4);
    }
    else if (sidecard_pos == 2) {
        _do_swap(2, 4);
    }
    else if  (sidecard_pos != 4) {
        cout << "ERROR" << endl;
    }
}

bool handtype::_two_pair() {
    // The cards are sorted, so if there are indeed two pair,
    // the fifth card is in the first, third, or fifth positions
    // (indices 0, 2, or 4)
    
    int pairs = 0;
    for (int i = 0; i < 4; i++) {
        if (_card[i].rank() == _card[i+1].rank()) {
            pairs++;
        }
    }

    if (pairs != 2) {
        return false;
    }
            
    if (_card[0].rank() != _card[1].rank()) {
            reorder_two_pair(0);
    }
    else if (_card[3].rank() != _card[4].rank()) {
            reorder_two_pair(4);
    }
    else {
        reorder_two_pair(2);
    }
            
    _rank = two_pair;
    _high = _card[0].rank();
    return true;
}

// if a pair is found, put the hand in canonical pair form
bool handtype::_pair_check( int index ) {
    if (_card[index].rank() != _card[index+1].rank()) {
        return false;
    }
    _high = _card[index].rank();
    _rank = one_pair;
    if (index != 0) { // otherwise hand is already in canonical form
        _do_swap(0, index);
        _do_swap(1, index+1);
        _do_sort(2, 4);
    }
    
    return true;
}

bool handtype::_one_pair() {
    for (int i = 0; i < 4; i++) {
        if (_pair_check(i)) {
            return true;
        }
    }
    return false;    
}

void handtype::_compute_rank() { 
    // assert(_rank != uninit);
    _do_sort(0, 4);
    if (_straight_flush()) return;
    if (_quad()) return;
    if (_full_house()) return;
    if (_flush()) return;
    if (_straight()) return;
    if (_trips()) return;
    if (_two_pair()) return;
    if (_one_pair()) return;
    _rank = high_card;
    _high = _card[0].rank();
}

void handtype::add_card( const card & c ) {
    _card[_insert_pt++] = c;
}

#ifdef DEBUG
void print_hand( const handtype & h) {
    for (int i = 0; i < 5; i++) {
        const card c = h.getcard(i);
        cout << c.rank() << c.suit() << " ";
    }
    cout << endl;
}
#endif

// return true and print left or right if the card[index] differs;
// otherwise print nothing and return false;
bool compare_cards(const handtype & left, const handtype & right, int index)
{
    int left_rank = left.getcard(index).rank(); 
    int right_rank = right.getcard(index).rank();
    if (left_rank > right_rank) {
        cout << "left" << endl;
        return true;
    }
    if (left_rank < right_rank) {
        cout << "right" << endl;
        return true;
    }
    return false;
}

void handle_two_pair_tie(const handtype & left, const handtype & right)
{
    // Hand will have been sorted high pair, low pair, side card.
    // High is set to rank of higher pair.
    if (left.high() > right.high()) {
        cout << "left" << endl;
        return;
    }
    if (left.high() < right.high()) {
        cout << "right" << endl;
        return;
    }
    
    // compare underpairs
    if (compare_cards(left, right, 2))
            return;
    
    // compare 5th (unpaired) card
    if (compare_cards(left, right, 4))
            return;
    
    // identical ranks of both pairs and 5th card
    cout << "none" << endl;
}

void handle_one_pair_tie(const handtype & left, const handtype & right) {
    // Hand will have been sorted high pair, other cards in sorted order
    // High is set to rank of pair.
    if (left.high() > right.high()) {
        cout << "left" << endl;
        return;
    }
    if (left.high() < right.high()) {
        cout << "right" << endl;
        return;
    }
    
    // Pairs are tied.  Examine the other three cards in turn.
    for (int i = 2; i < 5; i++) {
        if (compare_cards(left, right, i)) {
            return;
        }
    }
    
    // identical ranks of pair and the other 3 cards
    cout << "none" << endl;
}

void handle_no_pair_tie(const handtype & left, const handtype & right) {
    // Hand will have been sorted.
    // High is set to rank of highest card
    if (left.high() > right.high()) {
        cout << "left" << endl;
        return;
    }
    if (left.high() < right.high()) {
        cout << "right" << endl;
        return;
    }
    
    // High cards are tied.  Examine the other four cards in turn.
    for (int i = 1; i < 5; i++) {
        if (compare_cards(left, right, i)) {
            return;
        }
    }
    
    // identical ranks of pair and the other 3 cards
    cout << "none" << endl;
}

void handle_ties(const handtype & left, const handtype & right) {
    switch (left.getrank()) {
        case straight_flush:
        case straight:
            // Ace low, if supported, should have been handled in compute_rank
            if (left.high() > right.high())
                cout << "left";
            else if (left.high() < right.high())
                cout << "right";
            else
                cout << "none";
            cout << endl;
            return;
        case quad:
        case full_house:
        case trips:
            // These hands cannot be tied without community cards (e.g. Hold 'em)
            cout << "ERROR" << endl;
            return;
        case two_pair:
            handle_two_pair_tie(left, right);
            return;
        case one_pair:
            handle_one_pair_tie(left, right);
            return;
        case high_card:
        case phlush:
            handle_no_pair_tie(left, right);
            return;
        case uninit:
        default:
            cout << "ERROR" << endl;	
    }
}

void compare_hands_and_print( handtype & left, handtype & right )
{
#ifdef DEBUG
    print_hand(left);
    print_hand(right);
#endif
    if (left.rank() > right.rank())
        cout << "left" << endl;
    else if (left.rank() < right.rank())
        cout << "right" << endl;
    else {
        handle_ties(left, right);
        // hand ranks tied
#ifdef DEBUG
        cout << endl;
#endif
    }
} 

void parse_hand( istringstream & sinp, handtype & h ) {
    for (int i = 1; i <= 5; i++) {
        string tok; // actually two tokens - the rank and suit
        sinp >> tok;
        card c(tok[0], tok[1]);
        h.add_card(c);
    }
}

void parse_line( const string & line, handtype & left, handtype & right) {
    istringstream sinp(line);
    parse_hand(sinp, left);
    parse_hand(sinp, right);
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "usage: " << argv[0] << "<filename>\n";
        return 1;
    }

    ifstream ifs(argv[1]);
    string line;

    while (getline(ifs, line)) {
        handtype left, right;
        parse_line(line, left, right);
        compare_hands_and_print(left, right);
    } // while getline
}

// EOF
