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
int *stack;
int capacity = 1, top = -1;
void push(int);
int pop();
void stackFull();
int stackEmpty();
void printStack();

int main(void){
    MALLOC(stack, capacity * sizeof(*stack));
    int item[16];
    for(int i = 0; i < 16; i++)
        item[i] = i + 1;
    printStack();
    for(int i = 0; i < 8; i++){
        push(item[i]);
        printStack();
    }
    for(int i = 0; i < 9; i++){
        pop();
        printStack();
    }
    return 0;
}

void push(int item){
    if(top >= capacity - 1)
        stackFull();
    stack[++top] = item;
}

int pop(){
    if(top == -1)
        return stackEmpty();
    else{
        stack[top] = 0;
        return stack[top--];
    }
}

void stackFull(){
    printf("Stack is full, cannot add element, update capacity = %d -> %d\n", capacity, capacity * 2);
    REALLOC(stack, 2 * capacity * sizeof(*stack));
    capacity *= 2;
}

int stackEmpty(){
    printf("Stack is empty, cannot pop element\n");
    exit(EXIT_FAILURE);
}

void printStack(){
    for(int i = 0; i < capacity; i++)
        printf("%2d ", stack[i]);
    printf("\n");
}