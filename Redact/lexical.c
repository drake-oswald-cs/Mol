#include "defs.h"
#include "classAusiliaria.h"
extern FILE *fp;

int get_next(){
    return fgetc(fp); 
}

int peek(){
    int peek = fgetc(fp);
    fputc(peek, fp);
    return peek;
}

int scanint(int current){
    int digit, total = current;

    while(isdigit(peek())) {
        current = get_next();
        total = total * 10 + digit;
    }
    return total;
}

char* scanword(int current){
    char str[] = "";
    char ch = current;
    strncat(str, &ch, 1); 

    while(isalpha(peek())){
        ch = get_next();
        strncat(str, &ch, 1);
    }

    return str;
}

int scan(void){
    printf("%c", get_next());
}