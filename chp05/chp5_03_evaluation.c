#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MALLOC(p, s)\
    if(!((p) = malloc(s))){\
        fprintf(stderr, "Insufficient memory");\
        exit(EXIT_FAILURE);\
    }
typedef enum {
    not, and, or, true, false
} logical;
typedef struct node_s * treePointer;
typedef struct node_s {
    treePointer leftChild;
    logical data;
    int value;
    treePointer rightChild;
} node_t;
void postordereval(treePointer);

int main(void){
    treePointer start[7], X1, X2, X3;
    for(int i = 0; i < 7; i++)
        MALLOC(start[i], sizeof(treePointer));
    MALLOC(X1, sizeof(treePointer));
    MALLOC(X2, sizeof(treePointer));
    MALLOC(X3, sizeof(treePointer));
    {start[0]->leftChild = start[1];
    start[0]->data = or;
    start[0]->rightChild = start[2];
    start[1]->leftChild = start[3];
    start[1]->data = or;
    start[1]->rightChild = start[4];
    start[2]->data = not;
    start[2]->rightChild = X3;
    start[3]->leftChild = X1;
    start[3]->data = and;
    start[3]->rightChild = start[5];
    start[4]->leftChild = start[6];
    start[4]->data = and;
    start[4]->rightChild = X3;
    start[5]->data = not;
    start[5]->rightChild = X2;
    start[6]->data = not;
    start[6]->rightChild = X1;};
    
    //(A & !B) | (!A & C) | !C
    //(1 & !1) | (!1 & 1) | !1  -->  0 0 0 0 0 0 0
    X1->data = true;   
    X2->data = true;
    X3->data = true;
    //(1 & !0) | (!1 & 0) | !0  -->  1 1 1 1 0 1 0
    // X1->data = true;   
    // X2->data = false;
    // X3->data = false;

    postordereval(start[0]);
    printf("%d\n", start[0]->value);
    // for(int i = 0; i < 7; i++)
    //     printf("%d ", start[i]->value);
    // printf("\n");
    return 0;
}

void postordereval(treePointer node){
    if(node){
        postordereval(node->leftChild);
        postordereval(node->rightChild);
        switch(node->data){
            case not:
                node->value = !node->rightChild->value;
                break;
            case and:
                node->value = node->leftChild->value && node->rightChild->value;
                break;
            case or:
                node->value = node->leftChild->value || node->rightChild->value;
                break;
            case true:
                node->value = TRUE;
                break;
            case false:
                node->value = FALSE;
                break;
        }
    }
}

