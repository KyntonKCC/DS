#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p, s)\
    if(!((p) = malloc(s))){\
        fprintf(stderr, "Insufficient memory");\
        exit(EXIT_FAILURE);\
    }
#define REALLOC(p, s)\
    if(!((p) = realloc(p, s))){\
        fprintf(stderr, "Insufficient memory");\
        exit(EXIT_FAILURE);\
    }
typedef struct{
    int key;
}element;
element * queue;
int capacity = 2;
int front = 2 - 1, rear = -1;
void addq(element);
element deleteq();
void queueFull();
element queueEmpty();
void copy(const element *, const element *, element *);
void printQueue();

int main(void){
    MALLOC(queue, capacity * sizeof(element));
    element item[16];
    for(int i = 0; i < 16; i++)
        item[i].key = i+1;
    // printQueue();
    for(int i = 0; i < 8; i++){
        addq(item[i]);
        // printQueue();
    }
    for(int i = 0; i < 9; i++){
        element e = deleteq();
        // printQueue();
    }

    // test case
    // element e;
    // for(int i = 0; i < 7; i++){
    //     addq(item[i]);
    //     printQueue();
    // }
    // e = deleteq();
    // e = deleteq();
    // e = deleteq();
    // addq(item[7]);
    // addq(item[8]);
    // addq(item[9]);
    // printQueue();
    // addq(item[10]);
    // printQueue();
    // for(int i = 0; i < 9; i++){
    //     element e = deleteq();
    //     printQueue();
    // }
    return 0;
}

void addq(element item){
    rear = (rear + 1) % capacity;
    if(front == rear)
        queueFull();
    queue[rear] = item;
}

element deleteq(){
    element item;
    if(front == rear)
        return queueEmpty();
    else{
        front = (front + 1) % capacity;
        queue[front].key = 0;
        return queue[front];
    }
}

void queueFull(){
    printf("Stack is full, cannot add element, update capacity = %d -> %d\n", capacity, capacity * 2);
    element * newQueue;
    MALLOC(newQueue, 2 * capacity * sizeof(element));
    
    int start = (front + 1) % capacity;
    if(start < 2){
        // X X X O
        // O X X X
        copy(queue + start, queue + start + capacity - 1, newQueue);
    }else{
        // X O X X
        // X X O X
        copy(queue + start, queue + capacity, newQueue);
        copy(queue, queue + rear + 1, newQueue + capacity - start);
    }
    front = 2 * capacity - 1;
    rear = capacity - 1;
    capacity *= 2;
    free(queue);
    queue = newQueue;
}

element queueEmpty(){
    fprintf(stderr, "Queue is empty, cannot delete element\n");
    // exit(EXIT_FAILURE);
}

void copy(const element * first, const element * end, element * newQueue){
    int count = end - first;
    for(int i = 0; i < count; i++)
        (newQueue+i)->key = (first+i)->key;
}

void printQueue(){
    for(int i = 0; i < capacity; i++)
        printf("%2d ", queue[i].key);
    printf("\n");
}