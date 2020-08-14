#ifndef DEFS_H
#define DEFS_H
#include "defs.h"
#endif

#include "main.h"
#include "data.h"

void errorHandle(int error, Token peek){
    printf("MOLE Scan Error #%i, Line #%i:\n", error, peek.lineNum);
    switch(error){
        case 1:
            printf("Partial integer token, %s, exceeds 10 digits.\n", peek.STRvalue);
            break;
        case 2:
            printf("Absolute value of integer token, %s, exceeds 2^31 - 1.\n", peek.STRvalue);
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

struct Node* pushRule(struct Node* head, EntryType current, int* errorPt){
    Rule currentRule;
    while(head->data.type != 1){
        currentRule = parseTable[head->data.datum.nonTerminal][current.datum.terminal.token];
        if(currentRule.numOfEntries == 0){
            printf("Parse Error Line %i, Matched rule [%i][%i] doesn't exist.\n",
                    current.datum.terminal.lineNum, head->data.datum.nonTerminal,
                    current.datum.terminal.token);
            //printStack(head);
            *errorPt = 6;
        }
        /* printf("Rule Matched, Top: %i, Current: %i\n",
                head->data.datum.nonTerminal,  current.datum.terminal.token); 
        printStack(head); */
        if(currentRule.entries[0].type == 3){
            pop(&head);
        }
        else{
            pop(&head);
            for(int i = currentRule.numOfEntries - 1; i >= 0; i = i - 1){
                push(&head, currentRule.entries[i]);
            }
        }
    }
    return head;
}

struct Node* handleTerminal(struct Node* head, EntryType current, int* errorPt){
    if(current.datum.terminal.token == head->data.datum.terminal.token){
        /*printf("Terminal Matched, top: %i, Current: %i\n",
                head->data.datum.terminal.token, current.datum.terminal.token); */
        //printStack(head);
        pop(&head);
    }
    else{
        printf("Parse Error Line %i, Expected Terminal: %i, Terminal Scanned: %i\n",
                current.datum.terminal.lineNum,head->data.datum.terminal.token,
                current.datum.terminal.token);
        //printStack(head);
        *errorPt = 6;
    }
    return head;
}

int parse(FILE *fp) {
    buildTable(parseTable);
    Token top;
    Token peek;
    int error = 0;

    //Initialize the parsing stack by pushing the ending symbol, $.
    struct Node* head = NULL;
    EntryType temp;
    temp.type = 1;
    temp.datum.terminal.token = END;
    temp.datum.terminal.STRvalue = "$";
    temp.datum.terminal.lineNum = -1;
    push(&head, temp);

    //Push the first grammar rule onto the stack.
    temp.type = 0;
    temp.datum.nonTerminal = PROGRAM;
    push(&head, temp);

    //Reset temp value for scanning.
    temp.type = 1;

    //Read the first token and see if it is valid.
    error = scan(fp, &top, 1);
    if(error != 0){
        errorHandle(error, top);
        return 1;
    }
    if(error == 0 && top.token != 28){

        error = scan(fp, &peek, top.lineNum);
    }
    if(error != 0){
        errorHandle(error, peek);
        return 1;
    }

    //Going through the rest of the tokens and error handling.
    while(error == 0 && top.token != 28){
        temp.datum.terminal = top;
        while(head->data.type == 0){
            head = pushRule(head, temp, &error);
            if(error == 6){
                return 2;
            }
        }
        if(head->data.type == 1){
            head = handleTerminal(head, temp, &error);
            if(error == 6){
                return 3;
            }
        }
        
        top = peek;
        error = scan(fp, &peek, peek.lineNum);
    }
    if(error != 0){
        errorHandle(error, peek);
        return 1;
    }

    temp.datum.terminal = top;
    while(head->data.type == 0){
        head = pushRule(head, temp, &error);
    }
    if(head->data.type == 1){
        head = handleTerminal(head, temp, &error);
    }    

    return 0;
}