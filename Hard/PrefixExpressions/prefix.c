// Codeeval.com "prefix expressions"
/*
PREFIX EXPRESSIONS - CodeEval Hard challenge
CHALLENGE DESCRIPTION:

You are given a prefix expression. Write a program to evaluate it.

INPUT SAMPLE:

Your program should accept as its first argument a path to a filename.
The file contains one prefix expression per line. E.g.

* + 2 3 4
Your program has to read this and insert it into any data structure you
like. Traverse that data structure and evaluate the prefix expression.
Each token is delimited by a whitespace. You may assume that the only
valid operators appearing in test data are '+','*' and '/'

OUTPUT SAMPLE:

Print to stdout, the output of the prefix expression, one per line. E.g.

20

Constraints:
The evaluation result will always be an integer >= 0.
The number of the test cases is <= 40.

*/


// Must do computation in float (or double).  Answers will be integral, so cast to
// int to avoid printing decimal point and fractional part (all zeroes).

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    enum { plus, minus, mult, gozinta, integer } tok;
    float val;
} token;

void lexfile(FILE * f);

void lexinit();

token nexttok();

#define MAXLINE 1024

static char linebuf[MAXLINE];
static int pos; // index into linebuf;

static FILE * curfile; // don't like this but avoids file arguments everywhere

void finish(int code);

void lexfile(FILE * f) {
    curfile = f;
}

void lexinit() {
    if (!fgets(linebuf, MAXLINE, curfile))
	finish(0);
    pos = 0;
}

void strip_whitespace() {
    while (pos < MAXLINE && linebuf[pos] == ' ')
	++pos;
}

float getint() {
    int result = 0;
    while (linebuf[pos] >= '0' && linebuf[pos] <= '9' && pos < MAXLINE) {
	int charval = linebuf[pos] - '0';
	result = result * 10 + charval;
	++pos;
    }
    return (float)result;
}

token nexttok() { // note returns token by value;
    token t;
    strip_whitespace();
    switch (linebuf[pos]) {
	case '+':
	    t.tok = plus;
	    ++pos;
	    return t;
	case '-':
	    t.tok = minus;
	    ++pos;
	    return t;
	case '*':
	    t.tok = mult;
	    ++pos;
	    return t;
	case '/':
	    t.tok = gozinta;
	    ++pos;
	    return t;
	case (char)0: // end of line. Fetch another line
	case '\n':		 // and call nexttok recursively
	    lexinit(); // terminates (calling finish()) upon EOF
	    return nexttok();
	default:
	    if (linebuf[pos] >= '0' && linebuf[pos] <= '9') {
		t.tok = integer;
		t.val = getint(); //updates pos
		return t;
	    }
	    else {
		finish(1); // unexpected char in input - terminate
		return t; // will not get here
	    }
    } // switch
}

float get_operand();

float do_add() {
    float left = get_operand();
    float right = get_operand();
    return left + right;
}

float do_sub() {
    float left = get_operand();
    float right = get_operand();
    return left - right;
}

float do_mult() {
    float left = get_operand();
    float right = get_operand();
    return left * right;
}

float do_gozinta() {
    float left = get_operand();
    float right = get_operand();
    return left / right;
}

float get_operand() {
    token t = nexttok();
    switch (t.tok) {
	case plus:
	    return do_add();
	case minus:
	    return do_sub();
	case mult:
	    return do_mult();
	case gozinta:
	    return do_gozinta();
	case integer:
	    return t.val;
    }
    return 0; // silence warnings
}

void parse_and_eval() {
    while (1) {
	printf("%d\n", (int)get_operand());
    }
}

void finish(int code) {
    exit(code);
}

int main(int argc, char *argv[]) {
    FILE * f = fopen(argv[1], "r");
    
    lexfile(f);
    lexinit();

    parse_and_eval();
    
    exit(2); // should never get here - parse should call finish
}

