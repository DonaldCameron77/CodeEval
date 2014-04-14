"Advanced Calculator" from CodeEval

Parses via recursive descent. A major hurdle was the output
format - non-integral values must have 5 digits of precision
to the right of the decimal point, but with trailing zeros
suppressed.  This is surprisingly tricky in C++.

Largely based on Stroustrup: "Programming: Principles and Practice Using C++,"
but their calculator implementation had to be extended to support a
a number of operators and built-in functions, and to use a line from
a file argument as the basic unit of input (one expression per line).

The extensions forced introduction of a rudimenatary symbol table
(via std::map) for the built-in functions and the operator 'mod'.

'Mod' has higher precedence than '*' and '/'.  Unary minus is supposed
to have lower precedence (i.e., bind less tightly) than factorial, but this
was ignored, with the consequence that, e.g., -3! gets an error.  This
is not tested for by CodeEval, however.

Also, 6!! appears to be valid but does not work.  Again, this is not
tested for.

Currently the pass rate is 96/100.

