#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h> 

enum {
  RETURN, FN, IF, ELSE, TYPE, PRINT, EQUALS, LESS, EXCLAIM, PLUS, MINUS, TIMES,
  DIVIDE, SEMICOLON, COMMA, OPENCURL, CLOSECURL, OPENPAREN, CLOSEPAREN, OPENBRAKET,
  CLOSEBRAKET, IDENTIFIER, DIGIT, AND, OR, END 
};

typedef struct {
  int token;
  char *STRvalue;
  int lineNum;
}Token;

struct Node { 
  Token* data;
  struct Node* next;
};