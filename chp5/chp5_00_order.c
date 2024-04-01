#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE_STACK 50
#define MALLOC(p, s)\
    if(!((p) = malloc(s))){\
        fprintf(stderr, "Insufficient memory");\
        exit(EXIT_FAILURE);\
    }
typedef struct node_s * treePointer;
typedef struct node_s {
    treePointer leftChild;
    char data;
    treePointer rightChild;
} node_t;
//recursive
void inorder1(treePointer);     //LVR
void preorder1(treePointer);    //VLR
void postorder1(treePointer);   //LRV
//iterative
void inorder2(treePointer);     //LVR
void preorder2(treePointer);    //VLR
void postorder2(treePointer);   //LRV
void push(treePointer);
treePointer pop();
void stackFull();
treePointer stackEmpty();
treePointer stack[MAX_SIZE_STACK];
int top = -1;

/*
when I know VLR
use "reverse" to get RLV
use "left<->right" to get VRL
use "reverse" and "left<->right" to get LRV
*/

int main(void){
    treePointer start[9];
    for(int i = 0; i < 9; i++)
        MALLOC(start[i], sizeof(treePointer));
    {start[0]->leftChild = start[1];
    start[0]->data = '+';
    start[0]->rightChild = start[2];
    start[1]->leftChild = start[3];
    start[1]->data = '*';
    start[1]->rightChild = start[4];
    start[2]->data = 'E';
    start[3]->leftChild = start[5];
    start[3]->data = '*';
    start[3]->rightChild = start[6];
    start[4]->data = 'D';
    start[5]->leftChild = start[7];
    start[5]->data = '/';
    start[5]->rightChild = start[8];
    start[6]->data = 'C';
    start[7]->data = 'A';
    start[8]->data = 'B';};

    // {start[0]->leftChild = start[1];
    // start[0]->data = '-';
    // start[0]->rightChild = start[2];
    // start[1]->leftChild = start[3];
    // start[1]->data = '+';
    // start[1]->rightChild = start[4];
    // start[2]->leftChild = start[5];
    // start[2]->data = '/';
    // start[2]->rightChild = start[6];
    // start[3]->data = 'A';
    // start[4]->data = 'B';
    // start[5]->leftChild = start[7];
    // start[5]->data = '*';
    // start[5]->rightChild = start[8];
    // start[6]->data = 'E';
    // start[7]->data = 'C';
    // start[8]->data = 'D';};
    
    printf("------------Recursive------------");
    printf("\nInorder :\t");
    inorder1(start[0]);
    printf("\nPreorder :\t");
    preorder1(start[0]);
    printf("\nPostorder :\t");
    postorder1(start[0]);
    printf("\n------------Iterative------------");
    printf("\nInorder :\t");
    inorder2(start[0]);
    printf("\nPreorder :\t");
    preorder2(start[0]);
    printf("\nPostorder :\t");
    postorder2(start[0]);
    printf("\n");
    return 0;
}

void inorder1(treePointer ptr){
    if(ptr){
        inorder1(ptr->leftChild);
        printf("%c ", ptr->data);
        inorder1(ptr->rightChild);
    }
}

void preorder1(treePointer ptr){
    if(ptr){
        printf("%c ", ptr->data);
        preorder1(ptr->leftChild);
        preorder1(ptr->rightChild);
    }
}

void postorder1(treePointer ptr){
    if(ptr){
        postorder1(ptr->leftChild);
        postorder1(ptr->rightChild);
        printf("%c ", ptr->data);
    }
}

void inorder2(treePointer ptr){
    for(;;){
        for(; ptr; ptr = ptr->leftChild)
            push(ptr);
        if(top != -1) ptr = pop();
        if(!ptr) break;
        printf("%c ", ptr->data);
        ptr = ptr->rightChild;
    }
}

void preorder2(treePointer ptr){
    for(;;){
        for(; ptr; ptr = ptr->leftChild){
            printf("%c ", ptr->data);
            push(ptr);
        }
        if(top != -1) ptr = pop();
        if(!ptr) break;
        ptr = ptr->rightChild;
    }
}

void postorder2(treePointer ptr){
    char cheat[MAX_SIZE_STACK];
    int count = -1;
    for(;;){
        for(; ptr; ptr = ptr->rightChild){
            // printf("%c ", ptr->data);
            cheat[++count] = ptr->data;
            push(ptr);
        }
        if(top != -1) ptr = pop();
        if(!ptr) break;
        ptr = ptr->leftChild;
    }
    for(int i = count; i >= 0; i--)
        printf("%c ", cheat[i]);
}

void push(treePointer ptr){
    if(top >= MAX_SIZE_STACK - 1)
        stackFull();
    stack[++top] = ptr;
}

treePointer pop(){
    if(top == -1)
        return stackEmpty();
    return stack[top--];
}

void stackFull(){
    printf("Stack is full, cannot add element\n");
    exit(EXIT_FAILURE);
}

treePointer stackEmpty(){
    printf("Stack is empty, cannot pop element\n");
    exit(EXIT_FAILURE);
}
