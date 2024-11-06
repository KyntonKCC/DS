#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 8
int queue[MAX_QUEUE_SIZE];
int front = -1, rear = -1;
void addq(int);
int deleteq();
void queueFull();
int queueEmpty();

int main(void){
    int item[MAX_QUEUE_SIZE * 2];
    for(int i = 0; i < MAX_QUEUE_SIZE * 2; i++)
        item[i] = i + 1;
    for(int i = 0; i < MAX_QUEUE_SIZE; i++)
        printf("%d ", queue[i]);
    printf("\n");

    for(int i = 0; i < MAX_QUEUE_SIZE; i++)
        addq(item[i]);
    for(int i = 0; i < MAX_QUEUE_SIZE; i++)
        printf("%d ", queue[i]);
    printf("\n");

    for(int i = 0; i < MAX_QUEUE_SIZE; i++)
        deleteq();
    for(int i = 0; i < MAX_QUEUE_SIZE; i++)
        printf("%d ", queue[i]);
    printf("\n");
    return 0;
}

void addq(int num){
    if(rear == MAX_QUEUE_SIZE - 1)
        queueFull();
    else
        queue[++rear] = num;
}

int deleteq(){
    if(front == rear)
        return queueEmpty();
    else
        queue[++front] = 0;
        return queue[front];
}

void queueFull(){
    printf("FULL\n");
    exit(EXIT_SUCCESS);
}

int queueEmpty(){
    printf("EMPTY\n");
    exit(EXIT_SUCCESS);
}