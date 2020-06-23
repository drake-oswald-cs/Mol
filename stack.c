#include "defs.h"

void pop(struct Node** headRef) { 
    if (*headRef == NULL) 
        return; 

    struct Node* del = *headRef;

    *headRef = del->next; 
  
    free(del); 
    return; 
} 

void push(struct Node** headRef, Token* data) { 
    struct Node* pushNode = (struct Node*)malloc(sizeof(struct Node)); 
  
    pushNode->data = data; 
  
    pushNode->next = (*headRef); 
  
    (*headRef) = pushNode; 
}

/*int main(){
    Token* top;
    Token* mid;
    Token* fst;

    Token test;
    Token start;
    Token next;

    test.token = END;
    test.STRvalue = "$";
    test.lineNum = 0;
    fst = &test;

    start.token = FN;
    start.STRvalue = "fn";
    start.lineNum = 1;
    top = &start;

    next.token = IDENTIFIER;
    next.STRvalue = "main";
    next.lineNum = 1;
    mid = &next;

    struct Node* head = NULL;

    push(&head, fst);
    push(&head, top);
    push(&head, mid);

    printf("%s\n", head->data->STRvalue);

    pop(&head);

    printf("%s\n", head->data->STRvalue);

    pop(&head);

    printf("%s\n", head->data->STRvalue);

    pop(&head);

    if(head){
        printf("%s\n", head->data->STRvalue);
    }
}
*/