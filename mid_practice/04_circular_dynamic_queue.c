#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p, s) \
    if(!((p) = malloc(s))){ \
        printf("Insufficient memory"); \
        exit(EXIT_FAILURE); \
    }
#define REALLOC(p, s) \
    if(!((p) = realloc(p, s))){ \
        printf("Insufficient memory"); \
        exit(EXIT_FAILURE); \
    }
int *queue;
int capacity = 2, front = 2 - 1, rear = -1;
void addq(int);
int deleteq();
void queueFull();
int queueEmpty();
void copy(const int *, const int *, int *);
void printQueue();

int main(void){
    MALLOC(queue, capacity * sizeof(*queue));
    int item[16];
    for(int i = 0; i < 16; i++)
        item[i] = i + 1;
    printQueue();
    for(int i = 0; i < 7; i++){
        addq(item[i]);
        printQueue();
    }
    for(int i = 0; i < 6; i++){
        deleteq();
        printQueue();
    }
    for(int i = 7; i < 15; i++){
        addq(item[i]);
        printQueue();
    }
    return 0;
}

void addq(int item){
    rear = (rear + 1) % capacity;
    if(front == rear)
        queueFull();
    queue[rear] = item;
}

int deleteq(){
    if(front == rear)
        return queueEmpty();
    else{
        front = (front + 1) % capacity;
        queue[front] = 0;
        return queue[front];
    }
}

void queueFull(){
    printf("Stack is full, cannot add element, update capacity = %d -> %d\n", capacity, capacity * 2);
    int *newQueue;
    MALLOC(newQueue, 2 * capacity * sizeof(*newQueue));
    int start = (front + 1) % capacity;
    if(start < 2){
        copy(queue + start, queue + start + capacity - 1, newQueue);
    }else{
        copy(queue + start, queue + capacity, newQueue);
        copy(queue, queue + rear + 1, newQueue + capacity - start);
    }
    front = 2 * capacity - 1;
    rear = capacity - 1;
    capacity *= 2;
    free(queue);
    queue = newQueue;
}

int queueEmpty(){
    printf("EMPTY\n");
    exit(EXIT_SUCCESS);
}

void copy(const int *first, const int *end, int *newQueue){
    int count = end - first;
    for(int i = 0; i < count; i++)
        *(newQueue + i) = *(first + i);
}

void printQueue(){
    for(int i = 0; i < capacity; i++)
        printf("%2d ", queue[i]);
    printf("\n");
}