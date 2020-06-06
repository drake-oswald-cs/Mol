%option noyywrap
%{
  #include "mole.tab.h"
  #define YY_DECL int yylex()
%}

INTE [0-9]+

%%
[ \t\n]         ;
[#][a-zA-Z0-9 \t \n]+[#] ;

"return" return RETURN;
"fn"     return FN;
"if"     return IF;
"else"   return ELSE;
"int"|"bool"|"mat"|"vct" return TYPE;
"print"  return PRINT;
"="      return EQ;
"<"      return LT;
"?="     return EE;
"+"      return PL;
"-"      return MN;
"*"      return TM;
"/"      return DV;
";"      return SC;
","      return CM;
"{"      return OC;
"}"      return CC;
"("      return OP;
")"      return CP;
"["      return OB;
"]"      return CB;
"not"    return NG;
"and"    return AND;
"or"     return OR;
"true"|"false" return BL;
{INTE}    {yylval.num = atoi(yytext); return INT;} 
[a-zA-Z][a-zA-Z0-9]* {yylval.id = strdup(yytext); return ID;}

<<EOF>>     return END;

. ;

%%