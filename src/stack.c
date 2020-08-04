#ifndef DEFS_H
#define DEFS_H
#include "defs.h"
#endif

void pop(struct Node** headRef) { 
    if (*headRef == NULL) 
        return; 

    struct Node* del = *headRef;

    *headRef = del->next; 
  
    free(del); 
    return; 
} 

void push(struct Node** headRef, EntryType data) { 
    struct Node* pushNode = (struct Node*)malloc(sizeof(struct Node)); 
  
    pushNode->data = data; 
  
    pushNode->next = (*headRef); 
  
    (*headRef) = pushNode; 
}

void printStack(struct Node *node) 
{
    if(node == NULL){
        printf("Stack is empty\n");
    }
    while (node != NULL) 
    { 
        if(node->data.type == 0){
            printf("NonTerminal: %i\n", node->data.datum.nonTerminal);
        }
        if(node->data.type == 1){
            printf("Terminal: %i, Value: %s\n",node->data.datum.terminal.token,
                                        node->data.datum.terminal.STRvalue);
        }
        if(node->data.type == 3){
            printf("You have somehow ended up with an empty Node!\n"
                   "How curious, this should not be possible!!\n");
        }
        node = node->next; 
    } 
    printf("\n");
} 
