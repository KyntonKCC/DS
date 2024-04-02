#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MALLOC(p, s)\
    if(!((p) = malloc(s))){\
        fprintf(stderr, "Insufficient memory");\
        exit(EXIT_FAILURE);\
    }
typedef struct threadTree_s * threadPointer;
typedef struct threadTree_s {
    int leftThread;
    threadPointer leftChild;
    char data;
    threadPointer rightChild;
    int rightThread;
} threadTree_t;
threadPointer insucc(threadPointer);
void insertright(threadPointer, threadPointer);
void tinorder(threadPointer);

int main(void){
    threadPointer start[9], root, insert1, insert2;
    MALLOC(root, sizeof(* root));
    for(int i = 0; i < 9; i++)
        MALLOC(start[i], sizeof(* start[i]));
    MALLOC(insert1, sizeof(* insert1));
    MALLOC(insert2, sizeof(* insert2));
    {root->leftThread = FALSE;
    root->leftChild = start[0];
    root->data = 'R';
    root->rightChild = root;
    root->rightThread = FALSE;

    start[0]->leftThread = FALSE;
    start[0]->leftChild = start[1];
    start[0]->data = 'A';
    start[0]->rightChild = start[2];
    start[0]->rightThread = FALSE;

    start[1]->leftThread = FALSE;
    start[1]->leftChild = start[3];
    start[1]->data = 'B';
    start[1]->rightChild = start[4];
    start[1]->rightThread = FALSE;

    start[2]->leftThread = FALSE;
    start[2]->leftChild = start[5];
    start[2]->data = 'C';
    start[2]->rightChild = start[6];
    start[2]->rightThread = FALSE;

    start[3]->leftThread = FALSE;
    start[3]->leftChild = start[7];
    start[3]->data = 'D';
    start[3]->rightChild = start[8];
    start[3]->rightThread = FALSE;

    start[4]->leftThread = TRUE;
    start[4]->leftChild = start[1];
    start[4]->data = 'E';
    start[4]->rightChild = start[0];
    start[4]->rightThread = TRUE;

    start[5]->leftThread = TRUE;
    start[5]->leftChild = start[0];
    start[5]->data = 'F';
    start[5]->rightChild = start[2];
    start[5]->rightThread = TRUE;

    start[6]->leftThread = TRUE;
    start[6]->leftChild = start[2];
    start[6]->data = 'G';
    start[6]->rightChild = root;
    start[6]->rightThread = TRUE;

    start[7]->leftThread = TRUE;
    start[7]->leftChild = root;
    start[7]->data = 'H';
    start[7]->rightChild = start[3];
    start[7]->rightThread = TRUE;

    start[8]->leftThread = TRUE;
    start[8]->leftChild = start[3];
    start[8]->data = 'I';
    start[8]->rightChild = start[1];
    start[8]->rightThread = TRUE;
    
    insert1->leftThread = TRUE;
    insert1->leftChild = NULL;
    insert1->data = 'X';
    insert1->rightChild = NULL;
    insert1->rightThread = TRUE;

    insert2->leftThread = TRUE;
    insert2->leftChild = NULL;
    insert2->data = 'Y';
    insert2->rightChild = NULL;
    insert2->rightThread = TRUE;};
    
    tinorder(root);
    insertright(start[4], insert1);
    tinorder(root);
    insertright(start[0], insert2);
    tinorder(root);
    return 0;
}

threadPointer insucc(threadPointer tree){
    threadPointer temp;
    temp = tree->rightChild;
    if(!tree->rightThread)
        while(!temp->leftThread)
            temp = temp->leftChild;
    return temp;
}

void insertright(threadPointer s, threadPointer r){
    r->leftThread = TRUE;
    r->leftChild = s;
    r->rightChild = s->rightChild;
    r->rightThread = s->rightThread;
    s->rightChild = r;
    s->rightThread = FALSE;
    if(!r->rightThread){
        threadPointer temp = insucc(r);
        temp->leftChild = r;
    }
}

void tinorder(threadPointer tree){
    threadPointer temp = tree;
    while((temp = insucc(temp)) != tree)
        printf("%c ", temp->data);
    printf("\n");
}