#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 5
int queue[MAX_STACK_SIZE];
int rear = -1, front = -1;
void addq(int);
void deleteq();
void queueState();

int main(void){
    deleteq();
    addq(11);
    queueState();
    addq(22);
    addq(33);
    deleteq();
    addq(44);
    addq(55);
    queueState();
    addq(66);
    return 0;
}

void addq(int item){
    if(rear == MAX_STACK_SIZE - 1)
        fprintf(stderr, "Queue is full, cannot add element\n");
    else
        queue[++rear] = item;
}

void deleteq(){
    if(front == rear)
        fprintf(stderr, "Queue is empty, cannot delete element\n");
    else
        queue[++front];
}

void queueState(){
    if(front != rear)
        for(int i = front + 1; i <= rear; i++)
            printf("%d ", queue[i]);
    printf("\n");
}
