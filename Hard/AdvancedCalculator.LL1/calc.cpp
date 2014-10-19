/* ADVANCED CALCULATOR - CodeEval Hard challenge

CHALLENGE DESCRIPTION:

The goal of this challenge is to create an advanced calculator. 
The following operations should be supported with their order (operator precedence): 
    Pi        Pi number
    e         Euler's number
    sqrt()    Square root
    cos()     Cosine
    sin()     Sine
    tan()     Tangent
    lg()      Decimal logarithm
    ln()      Natural logarithm
1   ()        Brackets (i.e., parentheses)
2   ||        Absolute value, e.g. |-5 - 10|
3   !         Factorial
4   -         Unary minus
5   ^         Exponent
6   mod       Modulus divide, e.g. 5 mod 2 = 1 (only integers will be supplied here)
7   *, /      Multiply, Divide (left-to-right precedence)
8   +, -      Add, Subtract (left-to-right precedence)

INPUT SAMPLE:

Your program should accept as its first argument a path to a filename.
The input file contains several lines. Each line is one test case. Each
line contains mathematical expression. E.g.

250*14.3
3^6 / 117
(2.16 - 48.34)^-1
(59 - 15 + 3*6)/21
lg(10) + ln(e)
15*5 mod 2

OUTPUT SAMPLE:

For each set of input produce a single line of output which is the result of calculation.

3575
6.23077
−0.02165
2.95238
2
15
Note: Don't use any kind of eval function.

Constraints: 

Each number in input expression is greater than -20,000 and less than
20,000.  Each output number is greater than -20,000 and less than
20,000.  If output number is a float number it should be rounded to the
5th digit after the dot.  E.g 14.132646 gets 14.13265, 14.132644 gets
14.13264, 14.132645 gets 14.13265. 

If output number has less than 5 digits after the dot you don't need to
add zeros.  E.g. you need to print 16.34 (and not 16.34000) in case the
answer is 16.34.  And you need to print 16 (and not 16.00000) in case
the answer is 16.

*/

/*//////////////////////////////////////////////////////////////////////////////
	
	This calculator is implemented as a recursive-descent parser with on-the-fly
	evaluation. It differs from many toy examples in that a number of additional
	operations are included.  Note that exponentiation is right-associative, e.g.
	
		a^b^c is equivalent to a^(b^c)
		
	This differs from, e.g., 
	
		a * b / c which is rewritable as (a * b) / c
		
	There are also mod, absolute value, and factorial operators, each with its
	own precedence.  In normal practice, mod is left associative.  Does factorial
	have associativity, i.e., is 3!! an error?  Abs, like parens, does not have
	associativity ... although multiple symbols are involved (i.e., | -4 - 7 |) are
	needed, it is grammatically equivalent to a function call.
		
	Here is a possible grammar.  Note that brackets [] enclose an optional part of a
	production, braces {} enclose parts that may be repeated zero or more times, |
	separates alternatives, and unquoted parentheses provide grouping of elements. This
	discussion and grammar is per T. Norvell, 1999
	(http://www.engr.mun.ca/~theo/Misc/exp_parsing.htm)
	
        E --> T {( "+" | "-" ) T}
        T --> F {( "*" | "/" ) F}
        F --> P ["^" F]
        P --> v | "(" E ")" | "-" T
        
    This does not accomodate the extra elements in the problem statment.
    
    Here is a possible LL(1) (or nearly so ... -x*y is ambiguous) grammar using
    Norvell's notation, keeping in mind the precedence from the problem statement:
    
        1   ()
        2   ||      Absolute Value
        3   !       Factorial
        4   -       Unary minus
        5   ^       Exponent
        6   mod     Modulus
        7   *, /    Multiply, Divide
        8   +, -    Add, Subtract
        
    Among the binary operators, exponentiation is the only one that's right-associative
    
        Expr    --> Term {( '+' | '-' ) Term}
        
        Term    --> Modulo {( '*' | '/' ) Modulo}
        
        Modulo  --> Factor { 'mod' Factor }
        
        Factor  --> Primary [('^' Factor | '!']
        
        Primary --> Constant | '(' Expr ')' | ('-' | '+') Primary | '|' Expr '|' |
                    Func '(' Expr ')'
                    
        Func    --> 'sqrt |'sin' | 'cos' | 'tan' | 'lg' | 'ln'
        
        Constant--> Literal | Pi | e
        
    Putting Unary Minus into Primary and Factorial into Factor does not give Unary Minus
    the proper precedence with respect to Factorial (thus -7! will be treated
    as (-7)!, an error.  But it appears the test cases do not exploit this wrinkle.
        
     
	Per Norvell: "Note that the left-associative and the right-associative operators
	are treated differently; left-associative operators are consumed in a loop, while
	right-associative operators are handled with right-recursive productions. 
			
	This implementation uses one-character lookahead. That complicates token
	handling somewhat, as it's necessary to implement a token buffer so that
	tokens can be put back on the input if not consumed after looking ahead.
	
	Kludges:
	    Tokens remain single characters, and certain digits are code for
	    something else.
	    0: constant number (literal).  The value is in the val field of Token.
	       e and Pi are converted to their literal equivalents in the tokenizer.
	    1: sqrt
	    2: sin
	    3: cos
	    4: tan
	    5: lg
	    6: ln
	    7: mod
	    
	    This follows logically from Stroustrup's lead, but of course if enough
	    additional built in functions are introduced, we will have to extend beyond
	    single digits, or create an alternate mechanism.
	    
	    Using single chars to represent tokens and letting, e.g., '+' stand for itself
	    means there's a disconnect between single-char operators and things in the
	    symbol table.  Since symtable contents are all built-ins, it would be
	    cleaner if all tokens were represented the same way.
	    
	    Primary has '(' expr ')' and built-in-func '(' expr ')'.  If we had
	    a routine to handle '(' expr ')' specifically, we could use it for
	    both cases, saving code duplication.
	    
	   
/*////////////////////////////////////////////////////////////////////////////*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include <map>

#include <cmath> // ^ (pow), || (fabs/abs), factorial (tgamma),
                 // sqrt, sin, cos, tan, log10, log
// #define NDEBUG // uncomment after debug phase to suppress asserts
#include <cassert>

using namespace std;


/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; LEXER  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

// Token values

const char Number_tok   = '0'; // literals, e, and Pi
const char Sqrt_tok     = '1';
const char Sin_tok      = '2';
const char Cos_tok      = '3';
const char Tan_tok      = '4';
const char Lg_tok       = '5';
const char Ln_tok       = '6';
const char Mod_tok      = '7';

class Token {
public:
    char kind;      // what kind of token?
    double val;     // for numbers: a value 
    Token(char ch)  // make a Token from a char
        :kind(ch), val(0) { }    
    Token(char ch, double v)     // make a Token from a char and a double
        :kind(ch), val(v) { }
};

//------------------------------------------------------------------------------

class Token_stream {  // Singleton though it's not enforced
public: 
    /*
    Token_stream(): buffer(0) {} // needed for global constructor but new_line
								 // must be called before use
    */
    Token_stream();
    void new_line(string & line); // reinit Token_stream for next line
    Token nexttok();			// get a Token
    void putback(Token t);		// put Token back (note: used for parser putback ...
                                // whilst assembling tokens we use istringstream's
                                // putback)
private:
    bool full;					// is there a Token in the buffer?
    Token buffer;         // here is where we keep a Token put back using putback()
    map <string, char> symtbl;
    istringstream * issp; // read from here.  Must call new_line to
						  // (re)initialize for next line
};

extern Token_stream * tsp; // defined here ... this is for suppressing compiler warning

//------------------------------------------------------------------------------

// Note: the ctor merely sets 'full' to indicate that the buffer is empty:
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

Token_stream::Token_stream() : buffer(0) {
    symtbl.insert(make_pair("sqrt", Sqrt_tok));
    symtbl.insert(make_pair("sin",  Sin_tok));
    symtbl.insert(make_pair("cos",  Cos_tok));
    symtbl.insert(make_pair("tan",  Tan_tok));
    symtbl.insert(make_pair("lg",   Lg_tok));
    symtbl.insert(make_pair("ln",   Ln_tok));
    symtbl.insert(make_pair("mod",  Mod_tok));
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
    case '|':
    case '!':
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
            return Token(Number_tok, val);   // '0' is the 'kind' of a number;
        }
    case 'e':   // Euler's number
        return Token(Number_tok, M_E);
    case 'P':
        (*issp) >> ch; // consume the 'i' in Pi
        return Token (Number_tok, M_PI);
    case 'm': // "mod"
        (*issp) >> ch; (*issp) >> ch; // consume the 'od' in 'mod'
        return Token (Mod_tok);
    case 's': case 'c': case 't': case 'l':
        {
            string s;
            do {
                s.append(1, ch);
                (*issp) >> ch;
            } while (ch != '(');
            issp->putback(ch); // note NOT OUR LOCAL Token_stream::putback() !!
            return Token(symtbl.find(s)->second);
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
	additional exprs to the right (e.g., a + b - c + d).  See note above ...
	
*/

long double term();
long double modulo();
long double factor();
long double primary();

//  Expr --> Term {( '+' | '-' ) Term}
		
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

// Term --> Modulo {( '*' | '/' ) Modulo}

long double term()
{
    long double left = modulo();
    Token t = tsp->nexttok();
    
    do {
        switch (t.kind) {
        case '*':
            left *= modulo();
            t = tsp->nexttok();
            break;
        case '/':
            left /= modulo();
            t = tsp->nexttok();
            break;
        default:
            tsp->putback(t);
            return left;
        }
    } while (true);
}

// modulo  --> Factor { 'mod' Factor }

long double modulo()
{
    long double left = factor();
	Token t = tsp->nexttok();
	
	do {
	    switch (t.kind) {
	    case Mod_tok:
        {
            long iright = (long)factor();
            long ileft = (long)left;
            left = ileft % iright;
            t = tsp->nexttok();
            break;
        }
        default:
            tsp->putback(t);
            return left;
            }
	} while (true);
}

// Factor --> Primary [('^' Factor | '!']
//
// Note exponentiation is right associative, e.g. 2^3^4 is treated as 2^(3^4).
//
// Does 3!! work?  It appears CodeEval doesn't test for it.

long double factor()
{
    long double left = primary();
    Token t = tsp->nexttok();
    
    if (t.kind == '^') {
        long double right = factor();
        return pow(left, right);
    }
    else if (t.kind == '!')
        return tgamma(left + 1); // yup.  And it "works" for non-integers!  Negative #'s?
    else {
        tsp->putback(t);
        return left;
    }
}

/* 
    Changing format to enhance readability:
    
        Primary --> Constant
                    '(' Expr ')' 
                    '|' Expr '|'
                    '-' Primary
                    '+' Primary
                    Func '(' Expr ')'
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
    case '|': {	// '|' expr '|'
        long double q = expr();
        t = tsp->nexttok();
        assert(t.kind == '|');
        return fabs(q);
    }
    case '-':
        return - primary();
    case '+':
        return primary();
    case Sqrt_tok:  
    case Sin_tok:
    case Cos_tok:
    case Tan_tok:
    case Lg_tok:
    case Ln_tok:
    {    // should break out '(' expr ')' as a paren_expr() and use it for
        // primary and for func paren_expr
        Token ttmp = tsp->nexttok();
        assert(ttmp.kind == '(');
        long double arg = expr();
        ttmp = tsp->nexttok();
        assert(ttmp.kind == ')');
        switch (t.kind) {
        case Sqrt_tok:
            return sqrt(arg); 
        case Sin_tok:
            return sin(arg);
        case Cos_tok:
            return cos(arg);
        case Tan_tok:
            return tan(arg);
        case Lg_tok:
            return log10(arg);
        case Ln_tok:
            return log(arg);
        } // inner case for built-in funcs
    } // outer case for built-in funcs
    default:
        // using '0' as the tag for a constant number
        assert(t.kind == '0'); // always an error if not;
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
    
    outstr.erase(dotpos+6);
    
    // Then begin at min(outstr.size()-1, dotpos+5), ignoring nulls
    // and replacing '0' with nulls, until a nonzero digit is
    // seen or dotpos is reached.

#ifdef DEBUG
    cout << "size of outstr: " << outstr.size() << " ... outstr: ";

    for (unsigned long x = 0; x < outstr.size(); ++x) {
        cout << outstr[x] << " ";
    }
    cout << "end of outstr" << endl;
#endif

    unsigned long i;
    for (i = outstr.size()-1; i >= dotpos; --i) {
        // scan backwards until a nonzero digit or a '.' is found
        if (outstr[i] >= '1' && outstr[i] <= '9') {
            // nonzero digit - done, but keep this digit
            i++;
            break;
        }
        if (outstr[i] == '.') // - done, and we remove the '.' too
            break;
        // we reach here if looking at a '0' or maybe a null)
    }
    
    if (i < outstr.size())
        outstr.erase(i);  // nuke from outstr[i] to end

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
        fract = round(fract);
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
