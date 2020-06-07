#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

extern int scan(FILE *fp, Token *t, int lineNum);
extern int peek_Char(FILE *fp);
extern void pop(struct Node** headRef, struct Node* del);
extern void push(struct Node** headRef, Token* data);