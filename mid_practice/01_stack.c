#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 8
int stack[MAX_STACK_SIZE];
int top = -1;
void push(int);
int pop();
void stackFull();
int stackEmpty();

int main(void){
    int item[MAX_STACK_SIZE * 2];
    for(int i = 0; i < MAX_STACK_SIZE * 2; i++)
        item[i] = i + 1;
    for(int i = 0; i < MAX_STACK_SIZE; i++)
        printf("%d ", stack[i]);
    printf("\n");

    for(int i = 0; i < MAX_STACK_SIZE; i++)
        push(item[i]);
    for(int i = 0; i < MAX_STACK_SIZE; i++)
        printf("%d ", stack[i]);
    printf("\n");

    for(int i = 0; i < MAX_STACK_SIZE; i++)
        pop();
    for(int i = 0; i < MAX_STACK_SIZE; i++)
        printf("%d ", stack[i]);
    printf("\n");
    return 0;
}

void push(int num){
    if(top >= MAX_STACK_SIZE - 1)
        stackFull();
    else    
        stack[++top] = num;
}

int pop(){
    if(top == -1)
        return stackEmpty();
    else
        stack[top] = 0;
        return stack[top--];
}

void stackFull(){
    printf("FULL\n");
    exit(EXIT_SUCCESS);
}

int stackEmpty(){
    printf("EMPTY\n");
    exit(EXIT_SUCCESS);
}
