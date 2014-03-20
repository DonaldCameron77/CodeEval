/* SIMPLE CALCULATOR - CodeEval Moderate challenge
CHALLENGE DESCRIPTION:

The goal of this challenge is to create a simple calculator. 
The following operations should be supported with their order (operator precedence): 
1   ()       Brackets
2   -        Unary minus
3   ^        Exponent
4   *, /     Multiply, Divide (left-to-right precedence)
5   +, -     Add, Subtract (left-to-right precedence)

INPUT SAMPLE:

Your program should accept as its first argument a path to a filename. The input file contains several lines. Each line is one test case. Each line contains mathematical expression. E.g.

250*14.3
3^6 / 117
(2.16 - 48.34)^-1
(59 - 15 + 3*6)/21

OUTPUT SAMPLE:

For each set of input produce a single line of output which is the result of calculation.

3575
6.23077
−0.02165
2.95238
Note: Don't use any kind of eval function.

Constraints: 
Each number in input expression is greater than -20,000 and less than 20,000. 
Each output number is greater than -20,000 and less than 20,000. 
If output number is a float number it should be rounded to the 5th digit after the dot. 
E.g 14.132646 gets 14.13265, 14.132644 gets 14.13264, 14.132645 gets 14.13265. 

If output number has less than 5 digits after the dot you don't need to add zeros. 
E.g. you need to print 16.34 (and not 16.34000) in case the answer is 16.34. 
And you need to print 16 (and not 16.00000) in case the answer is 16.
*/

/*//////////////////////////////////////////////////////////////////////////////
	
	This calculator is implemented as a recursive-descent parser with on-the-fly
	evaluation. It differs from many toy examples in that an exponentiation
	operator is included.  Note that exponentiation is right-associative, e.g.
	
		a^b^c is equivalent to a^(b^c)
		
	This differs from, e.g., 
	
		a * b / c which is rewritable as (a * b) / c
		
	Here is a possible grammar:
	
		Expr:
			Term
			Term '+' Expr
			Term '-' Expr
			
		Term:
			Factor
			Term '*' Factor
			Term '/' Factor
			
		Factor:
			Primary
			Primary '^' Factor
			
		Primary:
			Constant
			'(' Expr ')'
			'-' Primary
			'+' Primary
		
	This grammar has already been rewritten in a form usable by an LL(1) parser.
	Often, one will see a rule like "Expr -> Expr + Term."  This is
	left-recursive, and if implemented literally would result in an infinite
	recursion in the routine for Expr.  These rules don't cause trouble for
	LR and LALR parsers, but don't work for LL parsers.
			
	This implementation uses one-character lookahead. That complicates token
	handling somewhat, as it's necessary to implement a token buffer so that
	tokens can be put back on the input if not consumed after looking ahead.
	
	This calculator should be easily extendable to implement the larger set of
	operations required for the Hard challenge "Advanced Calculator."
	However, I will likely try to use lex and yacc for that, to refresh my
	memory of those utilities.

/*////////////////////////////////////////////////////////////////////////////*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath> // powl()
// #define NDEBUG // uncomment after debug phase to suppress asserts
#include <cassert>

using namespace std;


/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; LEXER  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/


class Token {
public:
    char kind;        // what kind of token
    double val;     // for numbers: a value 
    Token(char ch)    // make a Token from a char
        :kind(ch), val(0) { }    
    Token(char ch, double v)     // make a Token from a char and a double
        :kind(ch), val(v) { }
};

//------------------------------------------------------------------------------

class Token_stream {  // Singleton though it's not enforced
public: 
    Token_stream(): buffer(0) {} // needed for global constructor but new_line
								 // must be called before use
    void new_line(string & line); // reinit Token_stream for next line
    Token nexttok();				// get a Token
    void putback(Token t);		// put a Token back
private:
    bool full;					// is there a Token in the buffer?
    Token buffer;     // here is where we keep a Token put back using putback()
    istringstream * issp; // read from here.  Must call new_line to
						 // (re)initialize for next line
};

//------------------------------------------------------------------------------

// The constructor just sets full to indicate that the buffer is empty:
void Token_stream::new_line(string & line) {
	static bool first = true;
	full = false;
	if (first) first = false;
	else delete issp;
	issp = new istringstream(line);
}

//------------------------------------------------------------------------------

// puts token back into the Token_stream's buffer
void Token_stream::putback(Token t)
{
    assert(! full); // can't putback() into a full buffer
    buffer = t;   
    full = true;
}

//------------------------------------------------------------------------------

Token Token_stream::nexttok()
{
    if (full) {       // do we already have a Token ready?
        // remove token from buffer
        full=false;
        return buffer;
    } 

    char ch = '\0'; // bug ... it appears that in some end-of-line situations,
    				// >> won't read anything into ch, so we get whatever
    				// leftover garbage was in there.  So init ch to our
    				// end-of-line indication - can't hurt.
    (*issp) >> ch;  // note that >> skips whitespace 

    switch (ch) {
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
        return Token(ch);        // let each character represent itself
    case '.':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        {    
            issp->putback(ch); // note NOT OUR LOCAL Token_stream::putback() !!
            double val;
            (*issp) >> val;              // read a floating-point number
            return Token('0',val);   // '0' is the 'kind' of a number;
        }
    default:
        assert(ch == '\0'); // end-of-line indication
        return Token(ch); 
    }
}

Token_stream * tsp; // points to a Token_stream local object in main()

/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; PARSER ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	For nonterminals involving left-associative grammar rules,
	iteration simplifies token handling and the consumption of
	additional exprs to the right (e.g., a + b - c + d)
	
		Expr:
			Term
			Term '+' Expr
			Term '-' Expr
*/


long double term();
long double factor();
long double primary();
		
long double expr()
{
	long double left = term();
	Token t = tsp->nexttok();
	
	do {
		switch (t.kind) {
		case '+':
			left += term();
			t = tsp->nexttok();
			break;
		case '-':
			left -= term();
			t = tsp->nexttok();
			break;
		default:
			tsp->putback(t);
			return left;
		}
	} while (true);
}

/*
	term() is almost a copy of expr, but one level down in the grammar.

		Term:
			Factor
			Term '*' Factor
			Term '/' Factor
*/

long double term()
{
	long double left = factor();
	Token t = tsp->nexttok();
	
	do {
		switch (t.kind) {
		case '*':
			left *= factor();
			t = tsp->nexttok();
			break;
		case '/':
			left /= factor();
			t = tsp->nexttok();
			break;
		default:
			tsp->putback(t);
			return left;
		}
	} while (true);
}

/**************************************************************************

	factor() must implement the right-associative rule for exponentiation.
	
		Factor:
			Primary
			Primary '^' Factor
*/

long double factor()
{
	long double left = primary();
	Token t = tsp->nexttok();
	
	if (t.kind == '^') {
		long double right = factor();
		return powl(left, right);
	}
	else {
		tsp->putback(t);
		return left;
	}
}

/*
		Primary:
			Constant
			'(' Expr ')'
			'-' Primary
			'+' Primary
*/

long double primary()
{
	Token t = tsp->nexttok();
	
	switch (t.kind) {
	case '(': {	// '(' expr ')'
		long double p = expr();
		t = tsp->nexttok();
		assert(t.kind == ')');
		return p;
	}
	case '-':
		return - primary();
	case '+':
		return primary();
	default:
		// using '0' as the tag for a constant number
		assert(t.kind == '0'); // always an error;
		return t.val;
	}
}

//;;;;;;;;;;;;;;;;;;;;;;;; Printing routines ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
// See the description header for printing constraints.  The requested format
// is not directly supported by C++ stream I/O

// "junk" == trailing zeros and '.'
string trim_trailing_junk(long double val)
{
	ostringstream sstream;
	sstream << fixed << setprecision(5);
	sstream << val;
	string outstr = sstream.str();

	unsigned long dotpos = outstr.find('.');
	assert(dotpos != string::npos);
	
	// we expect the ostringstream representation of a long double with a
	// fractional part (under /* fixed */ & setprecision(5)) to be
	// <wholeNumPart>'.'<digits><trailingZeros>, where digits
	// or trailing zeros (but not both?) may not be present.
	// Unfortunately there can be more than 5 fractional nonzero
	// digits present.  So first we null out anything beyond the first
	// 5 fractional places
	
	// Bug: what about rounding?  It seems, to get 5 fractional
	// digits with the rightmost digit rounded, you have to add
	// .00001 to the value if the 6th fractional digit is greater
	// than 5.

	outstr.erase(dotpos+6);
	
	// Then begin at min(outstr.size()-1, dotpos+5), ignoring nulls
	// and replacing '0' with nulls, until a nonzero digit is
	// seen or dotpos is reached.

	unsigned long i;
	for (i = outstr.size()-1; i >= dotpos; --i) {
		// scan backwards until a nonzero digit or a '.' is found
		if (outstr[i] >= '1' && outstr[i] <= '9') {
			// nonzero digit - we're done but keep this digit
			i++;
			break;
		}
		if (outstr[i] == '.') // - we're done and we'll remove the '.' too
			break;
		if (outstr[i] == '\0' ||  outstr[i] == '0') {
			// trailing 0 or perhaps a null(?) .. we'll zap it
			continue; 
		}	
	}
	
	if (i < outstr.size() - 1)
		outstr.erase(i);

	return outstr;
}

void print_dbl(long double val)
{
	cout << fixed << setprecision(5);

	const long double eps_kludge = 0.0000049999999999;
	
	if (abs(val - long(val)) < eps_kludge) {
		cout << long(val) << endl; // at least 5 zeros, then perhaps some junk
	}
	else {
		// deal with rounding the 5th decimal right of the decimal point
		bool negative = val < 0;
		long double da = abs(val);
		long i = long(da); 			// integral portion
		long double fract = da - i;		// fractional part
		fract = fract * 100000; 	// effectively a left shift 5 places.
		// 6th fractional digit (the millionth place) now in tenths place
		fract = floor(fract + 0.5);	// round
		fract = fract / 100000;  	// return it to its former magnitude
		long double new_d = i + fract;
		if (negative) new_d = - new_d;	// and Bob's your uncle
		
		// now trim trailing zeros (and decimal point, if applicable, though
		// I think the if clause dealt with a fractional part < 0.0000009999)
		string outstr = trim_trailing_junk(new_d);
		
		cout << outstr << endl;
	}
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;//

int main(int argc, char *argv[]) {
	if (argc != 2) {
    		cout << "usage: " << argv[0] << "<filename>\n";
    		return 1;
	}

	ifstream ifs(argv[1]);
	string line;
	
	cout << fixed << setprecision(5);

	while (getline(ifs, line))
	{
		Token_stream ts;
		tsp = & ts;
		ts.new_line(line);

		long double val = expr();
		
		print_dbl(val);
		
	} // while getline
}
