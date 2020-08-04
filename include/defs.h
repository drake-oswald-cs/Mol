#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h> 

enum {
  RETURN, FN, IF, ELSE, TYPE, PRINT, EQUALS, LESS, EXCLAIM, PLUS, MINUS, TIMES,
  DIVIDE, SEMICOLON, COMMA, OPENCURL, CLOSECURL, OPENPAREN, CLOSEPAREN, OPENBRAKET,
  CLOSEBRAKET, IDENTIFIER, INTEGER, BOOLEAN, AND, OR, VOPENBRAKET, DEQUALS, END
};

typedef enum {
  PROGRAM, DEF, FUNCTION, FORMALLIST, NEFORMAL, NEFORMALTAIL,
  FORMAL, BODY, NEBODY, STATEMENT, EXPR, EXPRTAIL, SIMPLEEXPR,
  SIMPLETAIL, TERM, TERMTAIL, FACTOR, FACTORTAIL, ASSIGN, ASSIGNTAIL,
  ACTUALS, NEACTUALS, NEATAIL, LITERAL, VECTOR, NUMLIST, NENUMLIST, 
  MATRIX, VCTLIST, NEVLIST, NEVLTAIL, NENTAIL
}NonTerminal;

typedef struct {
  int token;
  char *STRvalue;
  int lineNum;
}Token;

typedef struct{
  int type;
    union {
      NonTerminal nonTerminal;
      Token terminal;
    } datum;
} EntryType;

struct Node { 
  EntryType data;
  struct Node* next;
};

typedef struct{
  int numOfEntries;
  EntryType entries[9];
}Rule;

//Parse table would be a 2d array of Rules, where Rules are arrays of EntryType.
//columns Represent the Nonterminal enum, and rows represent the Terminal enum. 