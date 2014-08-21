// Cashreg.cpp - from CodeEval moderate challenge "Cash Register"

/*
CHALLENGE DESCRIPTION:

The goal of this challenge is to design a cash register program. You
will be given two float numbers. The first is the purchase price (PP) of
the item. The second is the cash (CH) given by the customer. Your
register currently has the following bills/coins within it:

'PENNY': .01,
'NICKEL': .05,
'DIME': .10,
'QUARTER': .25,
'HALF DOLLAR': .50,
'ONE': 1.00,
'TWO': 2.00,
'FIVE': 5.00,
'TEN': 10.00,
'TWENTY': 20.00,
'FIFTY': 50.00,
'ONE HUNDRED': 100.00

The aim of the program is to calculate the change that has to be returned to the customer.

INPUT SAMPLE:

Your program should accept as its first argument a path to a filename.
The input file contains several lines. Each line is one test case. Each
line contains two numbers which are separated by a semicolon. The first
is the Purchase price (PP) and the second is the cash(CH) given by the
customer. eg.

15.94;16.00
17;16
35;35
45;50
OUTPUT SAMPLE:

For each set of input produce a single line of output which is the
change to be returned to the customer. In case the CH < PP, print out
ERROR. If CH == PP, print out ZERO. For all other cases print the amount
that needs to be returned, in terms of the currency values provided. The
output should be sorted in highest-to-lowest order (DIME,NICKEL,PENNY).
eg.

NICKEL,PENNY
ERROR
ZERO
FIVE

*/


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

const char * names [] = { "PENNY", "NICKEL", "DIME", "QUARTER", "HALF DOLLAR",
                          "ONE", "TWO", "FIVE", "TEN", "TWENTY", "FIFTY", "ONE HUNDRED" };
		
const float values [] = { .01, .05, .10, .25, .50,
                         1.00, 2.00, 5.00, 10.00, 20.00, 50.00, 100.00 };
		
float cash_on_hand;

const int numvals = sizeof(values)/sizeof(float);

bool floatEqual(float a, float b) {
    const float eps = 0.0001;
    return fabs(a-b) < eps;
}

void set_cash_on_hand() {
    // int numvals = sizeof(values)/sizeof(float);
    cash_on_hand = 0.0;
    for (int i = 0; i < numvals; i++) {
        cash_on_hand += values[i];
    }
#ifdef DEBUG
    cout << "cash_on_hand is " << cash_on_hand << endl;
#endif
}

// print denoms needed in smaller-to-larger order
void select_and_print_denoms( float change_needed )
{
#ifdef DEBUG
    cout << "SELECT_AND_PRINT_DENOMS - change needed: " << change_needed << endl;
    float total_change = 0.0;
#endif	
    for (int i = numvals-1; i >= 0; --i)
    {
        while (change_needed > values[i]
               || floatEqual(change_needed, values[i])) // fp hack for >=
        {
            change_needed -= values[i];
#ifdef DEBUG
            total_change += values[i];
#endif
            cout << names[i];
            if (!floatEqual(change_needed, 0.0))
                cout << ',';
        }
    } // for
    
    cout << endl;
#ifdef DEBUG
    cout << "total change = " << total_change << "\n" << endl;
#endif
}

void make_change(float purchase_price, float cash_tendered)
{
#ifdef DEBUG
    cout << "MAKE_CHANGE:: purchase_price = " << purchase_price
            << ", cash_tendered = " << cash_tendered << endl;
#endif
    float change_needed = cash_tendered - purchase_price;
    bool zeroNeeded = floatEqual(change_needed, 0.0);
    if (!zeroNeeded && change_needed < 0.0) {
        cout << "ERROR" << endl;
    }
    else if (zeroNeeded) {
        cout << "ZERO" << endl;
    }
    else {
        select_and_print_denoms(change_needed);
    }
}

void do_change_maker( ifstream& the_file ) {
    set_cash_on_hand();
    float purchase_price, cash_tendered;
    while (the_file >> purchase_price) {
        char delim;
        the_file >> delim;
        if (delim != ';') {
            cout << "Fail - unexpected delimiter";
            break;
        }
        else {
            the_file >> cash_tendered;
            make_change(purchase_price, cash_tendered);
        }
    } // while
}

int main ( int argc, char *argv[] )
{
    if ( argc != 2 )
        cout << "usage: " << argv[0] << " <filename>" << endl;
    else {
        ifstream the_file ( argv[1] );
        if ( !the_file.is_open() )
            cout << "Could not open file" << endl;
        else {
            do_change_maker(the_file);
        }
    }
}

// EOF
