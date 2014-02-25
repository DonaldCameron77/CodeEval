#
# Makefile for levenshtein distance - CodeEval Hard challenge
#

IDIR=.

CPP=clang++

DEBUGFLAGS=-g
#DEBUGFLAGS=-g -DDEBUG

CPPFLAGS=-I$(IDIR) -g -std=c++11 -stdlib=libc++ -Weverything -Wno-logical-op-parentheses -Wno-c++98-compat -Wno-missing-prototypes

ODIR=.
# LDIR =../lib

# LIBS=-lm

_DEPS = dict.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = lev.o dictset.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cpp $(DEPS)
	$(CPP) -c -o $@ $< $(CPPFLAGS) $(DEBUGFLAGS)

a.out: $(OBJ)
	$(CPP) -o $@ $^ $(CPPFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

