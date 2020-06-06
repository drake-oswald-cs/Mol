#include "defs.h"
#include "main.h"

void errorHandle(int error, Token peek){
    printf("MOLE Scan Error #%i, Line #%i:\n", error, peek.lineNum);
    switch(error){
        case 1:
            printf("Partial integer token, %s, exceeds 10 digits.\n", peek.STRvalue);
            break;
        case 2:
            printf("Absolute value of integer token, %s, exceeds 2^32 - 1.\n", peek.STRvalue);
            break;
        case 3:
            printf("Partial identifier token, %s, exceeds 31 characters.\n", peek.STRvalue);
            break;
        case 4:
            printf("Invalid token '%s'.\n", peek.STRvalue);
            break;
        case 5:
            printf("Improper comments missing '#'.\n");
            break;
        default:
            printf("Unknown error.");
    }
}


int main(int argc, char *argv[]) {
    FILE *fp;
    Token top;
    Token peek;
    int error = 0;
 
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
    error = scan(fp, &top, 1);
    if(error != 0){
        errorHandle(error, top);
        return 1;
    }
    if(error == 0 && top.token != 25){
        error = scan(fp, &peek, top.lineNum);
    }
    if(error != 0){
        errorHandle(error, peek);
        return 1;
    }

    //Going through the rest of the tokens and error handling.
    while(error == 0 && peek.token != 25){
        printf("Enum: %i  Value: %s  Line: %i\n", top.token, top.STRvalue, top.lineNum);
        top = peek;
        error = scan(fp, &peek, peek.lineNum);
    }
    if(error != 0){
        errorHandle(error, peek);
        return 1;
    }
    printf("Enum: %i  Value: %s  Line: %i\n", peek.token, peek.STRvalue, top.lineNum);

    //Closing the file ending main.
    fclose(fp);
    return 0;
    }