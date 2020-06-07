#include "defs.h"

#define MAXSTRING 32
#define MAXDIGIT 10
int error =  0;

int next_Char(FILE *fp){
    return fgetc(fp); 
}

int peek_Char(FILE *fp){
    int see = fgetc(fp);
    ungetc(see, fp);
    return see;
}

char* scanint(FILE *fp, int current){
    char *str;
    str = (char *) malloc(sizeof(char) * (MAXDIGIT + 2));

    int i = 0;
    long total = 0;
    char ch = (char) current;
    if (current == '-'){
        *(str + i) = ch;
        i++;
        ch = next_Char(fp);
    }
    else{
       *(str + i) = '+'; 
       i++;
    }

    while((i <= (MAXDIGIT)) && isdigit(ch)){
        *(str+i) = ch;
        total = (total * 10) + (ch - '0'); 
        ch = next_Char(fp);
        i++;
    }

    ungetc(ch, fp);

    if(isdigit(peek_Char(fp))){
        error = 1;
    }

    else if(total >= 4294967296){
        error = 2;
    }

    *(str+i) = '\0';

    return str;
}

char* scanword(FILE *fp, int current){
    char *str;
    str = (char *) malloc(sizeof(char) * (MAXSTRING+1));

    int i = 0;
    char ch = (char) current;

    while((i < (MAXSTRING - 1)) && isalpha(ch)){
        //printf("current = %c\n", ch);
        *(str+i) = ch;
        ch = next_Char(fp);
        i++;
    }

    ungetc(ch, fp);

    if(isalpha(peek_Char(fp))){
        error = 3;
    }

    *(str+i) = '\0';

    return str;
}

int scan(FILE *fp, Token *t, int lineNum){

    while(' ' == peek_Char(fp) || '\t' == peek_Char(fp) ||
        '\n' == peek_Char(fp) || '\r' == peek_Char(fp) || 
        '\f' == peek_Char(fp) || '#' == peek_Char(fp)){

        if(peek_Char(fp) == '#'){
            next_Char(fp);
            int next = 1;
            while(next){
                if(peek_Char(fp) == '#'){
                    next_Char(fp);
                    next = 0;
                }
                else{
                    if(peek_Char(fp) == '\n'){
                        lineNum++;
                    }
                    next_Char(fp);
                }
                if(peek_Char(fp) == EOF){
                    error = 5;
                    next = 0;
                }
                
            }
        }
        else{
            if(peek_Char(fp) == '\n'){
                lineNum++;
            }
            next_Char(fp);
        }
    }

    int current = next_Char(fp);

    t->lineNum = lineNum;

    if(isdigit(current)){
        t->token = DIGIT;
        t->STRvalue = scanint(fp, current);
    }


    else if(isalpha(current)){
        char* swap = scanword(fp, current);
        if(!strcmp(swap, "and")){
            t->token = AND;
            t->STRvalue = swap;
        }
        else if(!strcmp(swap, "or")){
            t->token = OR;
            t->STRvalue = swap;
        }
        else if(!strcmp(swap, "return")){
            t->token = RETURN;
            t->STRvalue = swap;
        }
        else if(!strcmp(swap, "print")){
            t->token = PRINT;
            t->STRvalue = swap;
        }
        else if(!strcmp(swap, "fn")){
            t->token = FN;
            t->STRvalue = swap;
        }
        else if(!strcmp(swap, "if")){
            t->token = IF;
            t->STRvalue = swap;
        }
        else if(!strcmp(swap, "else")){
            t->token = ELSE;
            t->STRvalue = swap;
        }
        else if(!strcmp(swap, "int") || !strcmp(swap, "bol") ||
            !strcmp(swap, "vct") || !strcmp(swap, "mat")){
                
            t->token = TYPE;
            t->STRvalue = swap;
        }
        else{
            t->token = IDENTIFIER;
            t->STRvalue = swap;
        }
    }

    else switch (current){
        case EOF:
            t->token = END;
            t->STRvalue = "$";
            break; 
        case '+':
            t->token = PLUS;
            t->STRvalue = "+";
            break;
        case '-':
            if isdigit(peek_Char(fp)){
                t->STRvalue = scanint(fp, current);
                t->token = DIGIT;
            }
            else{
                t->token = MINUS;
                t->STRvalue = "-";
            }
            break;
        case '*':
            t->token = TIMES;
            t->STRvalue = "*";
            break;
        case '/':
            t->token = DIVIDE;
            t->STRvalue = "/";
            break;
        case '(':
            t->token = OPENPAREN;
            t->STRvalue = "(";
            break;
        case ')':
            t->token = CLOSEPAREN;
            t->STRvalue = ")";
            break;
        case '[':
            t->token = OPENBRAKET;
            t->STRvalue = "[";
            break;
        case ']':
            t->token = CLOSEBRAKET;
            t->STRvalue = "]";
            break;
        case '{':
            t->token = OPENCURL;
            t->STRvalue = "{";
            break;
        case '}':
            t->token = CLOSECURL;
            t->STRvalue = "}";
            break;
        case ',':
            t->token = COMMA;
            t->STRvalue = ",";
            break;
        case '=':
            t->token = EQUALS;
            t->STRvalue = "=";
            break;
        case '<':
            t->token = LESS;
            t->STRvalue = "<";
            break;
        case ';':
            t->token = SEMICOLON;
            t->STRvalue = ";";
            break;
        case '!':
            t->token = EXCLAIM;
            t->STRvalue = "!";
            break;
        default:
            error = 4;
            char *str;
            str = (char *) malloc(sizeof(char) * 2);
            *(str+0) = current;
            *(str+1) = '\0';
            t->STRvalue = str;
            t->token = IDENTIFIER;
    }

    return error;
}