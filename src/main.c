#ifndef DEFS_H
#define DEFS_H
#include "defs.h"
#endif

#include "main.h"

int main(int argc, char *argv[]) {
    FILE *fp;
    int parseError;

    //Open up the file.
    if((argv[1][strlen(argv[1])-1] == 'l') &&
       (argv[1][strlen(argv[1])-2] == 'o') &&
       (argv[1][strlen(argv[1])-3] == 'm') &&
       (argv[1][strlen(argv[1])-4] == '.')){
           fp = fopen(argv[1], "r+");
    }
    else{
        printf("Incorrect file extension\n");
        return 1;
    }
    if(fp == NULL){
        printf("File %s does not exist\n",argv[1]);
        return 1;
    }

    //Initializing token stack and error handling.
    parseError = parse(fp);

    if(parseError == 0){
        printf("Program, %s, is syntatically valid.\n", argv[1]);
    }

    //Closing the file ending main.
    fclose(fp);
    return 0;
}