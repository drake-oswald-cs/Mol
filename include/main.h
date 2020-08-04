#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

extern int scan(FILE *fp, Token *t, int lineNum);
extern int peek_Char(FILE *fp);
extern void pop(struct Node** headRef);
extern void push(struct Node** headRef, EntryType data);
extern void printStack(struct Node *node);
extern int parse(FILE *fp);
extern void buildTable(Rule parseTable[32][29]);