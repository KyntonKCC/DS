#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 5
int stack[MAX_STACK_SIZE];
int top = -1;
void push(int);
void pop();
void stackState();

int main(void){
    pop();
    push(11);
    stackState();
    push(22);
    pop();
    push(33);
    push(44);
    pop();
    push(55);
    stackState();
    push(66);
    pop();
    push(77);
    push(88);
    pop();
    push(99);
    stackState();
    push(111);
    return 0;
}

void push(int item){
    if(top >= MAX_STACK_SIZE - 1)
        fprintf(stderr, "Stack is full, cannot add element\n");
    else
        stack[++top] = item;
}

void pop(){
    if(top < 0)
        fprintf(stderr, "Stack is empty, cannot pop element\n");
    else
        stack[top--];
}

void stackState(){
    if(top >= 0)
        for(int i = 0; i <= top; i++)
            printf("%d ", stack[i]);
    printf("\n");
}
