#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE 10
#define MALLOC(p, s)\
    if(!((p) = malloc(s))){\
        fprintf(stderr, "Insufficient memory");\
        exit(EXIT_FAILURE);\
    }
typedef struct{
    int key;
}element;
typedef struct queue * queuePointer;
struct queue{
    element data;
    queuePointer link;
};
queuePointer top[MAX_QUEUE];
void printQueue();
void addq(element);
element deleteq();
int front = -1, rear = -1;

int main(void){
    element number[9] = {11, 22, 33, 44, 55, 66, 77, 88, 99};
    element e;
    addq(number[0]);
    addq(number[1]);
    addq(number[2]);
    printQueue();
    e = deleteq();
    e = deleteq();
    printQueue();
    addq(number[3]);
    addq(number[4]);
    addq(number[5]);
    e = deleteq();
    e = deleteq();
    printQueue();
    addq(number[6]);
    addq(number[7]);
    e = deleteq();
    addq(number[8]);
    printQueue();
    return 0;
}

void printQueue(){
    printf("The queue contents : ");
    for(int i = front + 1; i <= rear; i++)
        printf("%4d", top[i]->data.key);
    printf("\n");
}

void addq(element item){
    queuePointer temp;
    MALLOC(temp, sizeof(queuePointer));
    temp->data = item;
    temp->link = top[++rear];
    top[rear] = temp;
}

element deleteq(){
    queuePointer temp = top[++front];
    if(!temp){
        fprintf(stderr, "Stack is empty!!!\n");
        exit(EXIT_FAILURE);
    }
    element item = temp->data;
    top[front] = temp->link;
    free(temp);
    return item;
}
