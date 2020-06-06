#include <stdio.h>
#include <string.h>
 
#define MAXCHAR 1000

void wspl(char* str){
	char spc[] = ",;(){}[]#";
    char stream[]= "";

	for(int i = 0; i<strlen(str); i++){
        char current = str[i];
        if (strchr(spc, current)){
            printf("%c\n", current);    
        }
    }
    //printf("%s", stream);
	
}

int main(int argc, char *argv[]) {
    FILE *fp;
    char str[MAXCHAR];
 
    fp = fopen(argv[1], "r");

    if (fp == NULL){
        printf("Could not open file %s \n",argv[1]);
        return 1;
    }
    
    while (fgets(str, MAXCHAR, fp) != NULL){
        printf("%s\n\n", str);    
    }

    fclose(fp);
    return 0;
}