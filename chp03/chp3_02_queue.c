#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 8
typedef struct{
    int key;
}element;
element queue[MAX_STACK_SIZE];
int rear = -1, front = -1;
void addq(element);
element deleteq();
void queueFull();
element queueEmpty();

int main(void){
    element item[MAX_STACK_SIZE + 1];
    for(int i = 0; i < MAX_STACK_SIZE + 1; i++)
        item[i].key = i+1;
    // for(int i = 0; i < MAX_STACK_SIZE; i++)
    //     printf("%d ", queue[i].key);
    // printf("\n");
    for(int i = 0; i < MAX_STACK_SIZE + 1; i++)
        addq(item[i]);
    // for(int i = 0; i < MAX_STACK_SIZE; i++)
    //     printf("%d ", queue[i].key);
    // printf("\n");
    for(int i = 0; i < MAX_STACK_SIZE + 1; i++){
        element e = deleteq();
    }
    // for(int i = 0; i < MAX_STACK_SIZE; i++)
    //     printf("%d ", queue[i].key);
    // printf("\n");
    return 0;
}

void addq(element item){
    if(rear == MAX_STACK_SIZE - 1)
        queueFull();
    else
        queue[++rear] = item;
}

element deleteq(){
    if(front == rear)
        return queueEmpty();
    else{
        queue[++front].key = 0;
        return queue[front];
    }
}

void queueFull(){
    fprintf(stderr, "Queue is full, cannot add element\n");
    // exit(EXIT_FAILURE);
}

element queueEmpty(){
    fprintf(stderr, "Queue is empty, cannot delete element\n");
    // exit(EXIT_FAILURE);
}