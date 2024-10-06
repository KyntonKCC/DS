#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE_QUEUE 50
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
void levelorder(treePointer);
void addq(treePointer);
treePointer deleteq();
void queueFull();
treePointer queueEmpty();
treePointer queue[MAX_SIZE_QUEUE];
int front = -1, rear = -1;


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
    
    levelorder(start[0]);
    printf("\n");
    return 0;
}

void levelorder(treePointer ptr){
    if(!ptr) return;
    addq(ptr);
    for(;;){
        ptr = deleteq();
        if(ptr){
            printf("%c ", ptr->data);
            if(ptr->leftChild)
                addq(ptr->leftChild);
            if(ptr->rightChild)
                addq(ptr->rightChild);
        }
        if(front == rear && front != 0)
            break;
    }
}

void addq(treePointer ptr){
    if(rear == MAX_SIZE_QUEUE - 1)
        queueFull();
    queue[++rear] = ptr;
}

treePointer deleteq(){
    if(front == rear)
        return queueEmpty();
    return queue[++front];
}

void queueFull(){
    printf("Queue is full, cannot add element\n");
    exit(EXIT_FAILURE);
}

treePointer queueEmpty(){
    printf("Queue is empty, cannot delete element\n");
    exit(EXIT_FAILURE);
}