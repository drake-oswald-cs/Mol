%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern int yyparse();
extern FILE* yyin;

void yyerror(const char* s);
%}

%union {int num; char *id;}
%start Program
%token RETURN 
%token FN 
%token IF 
%token ELSE 
%token TYPE 
%token PRINT 
%token EQ 
%token LT 
%token EE 
%token PL 
%token MN 
%token TM 
%token DV 
%token SC 
%token CM 
%token OC 
%token CC 
%token OP 
%token CP 
%token OB 
%token CB 
%token NG
%token AND
%token OR
%token END 
%token <num> INT 
%token <id> ID 
%token BL
%left EE LT PL MN OB NG AND OR INT ID BL TM DV OP


%%
Program : Def END

Def : Function Def
    | %empty
    ;

Function : FN ID OP FormalList CP TYPE OC Body CC
         ;

FormalList : NEFormal
           | %empty
           ;

NEFormal : Formal NEFormal-Tail
         ;

NEFormal-Tail : CM NEFormal
              | %empty
              ;
              
Formal : TYPE ID
       ;

Body : NEBody;
     | %empty

NEBody : Statement SC Body;

Statement : Declaration 
          | Print
          | If
          | Expr
          | Return;
   
Declaration : TYPE ID EQ Expr;

Print : PRINT OP Expr CP;

If : IF Expr OC Body CC ELSE OC Body CC;

Return : RETURN Expr;

Expr : Simple-Expr Expr-Tail;

Simple-Expr : Term Simple-Tail;

Expr-Tail : LT Expr
          | EE Expr
          | Simple-Expr
          ;

Term : Factor Term-Tail;

Simple-Tail : OR Simple-Expr
            | PL Simple-Expr
            | MN Simple-Expr
            | Term
            ;

Term-Tail : AND Term
          | TM Term
          | DV Term
          | Factor
          ;

Factor : NG Factor
       | ID Factor-Tail
       | Literal
       | MN Factor
       | OP Expr CP;

Factor-Tail : OP Actuals CP
                | OB Assign CB EQ Expr
                | EQ Expr
                ;


Assign : Expr Assign-Tail
       ;

Assign-Tail : SC Expr
            | %empty
            ;
                
Actuals : NEActuals
        | %empty
        ;

NEActuals : Expr NEA-Tail;

NEA-Tail : CM NEActuals
         | %empty
         ;
          
Literal : INT
        | BL
        | VM
        ;

VM : OB List CB

List : INT List
     | SC  List
     | %empty

%%
int main() {
	yyin = stdin;

	do {
		yyparse();
	} while(!feof(yyin));

	return 0;
}

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}
