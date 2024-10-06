#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 8
typedef struct{
    int key;
}element;
element stack[MAX_STACK_SIZE];
int top = -1;
void push(element);
element pop();
void stackFull();
element stackEmpty();

int main(void){
    element item[MAX_STACK_SIZE + 1];
    for(int i = 0; i < MAX_STACK_SIZE + 1; i++)
        item[i].key = i+1;
    // for(int i = 0; i < MAX_STACK_SIZE; i++)
    //     printf("%d ", stack[i].key);
    // printf("\n");
    for(int i = 0; i < MAX_STACK_SIZE + 1; i++)
        push(item[i]);
    // for(int i = 0; i < MAX_STACK_SIZE; i++)
    //     printf("%d ", stack[i].key);
    // printf("\n");
    for(int i = 0; i < MAX_STACK_SIZE + 1; i++){
        element e = pop();
    }
    // for(int i = 0; i < MAX_STACK_SIZE; i++)
    //     printf("%d ", stack[i].key);
    // printf("\n");
    return 0;
}

void push(element item){
    if(top >= MAX_STACK_SIZE - 1)
        stackFull();
    else
        stack[++top] = item;
}

element pop(){
    if(top == -1){
        return stackEmpty();
    }else{
        stack[top].key = 0;
        return stack[top--];
    }
}

void stackFull(){
    fprintf(stderr, "Stack is full, cannot add element\n");
    // exit(EXIT_FAILURE);
}

element stackEmpty(){
    fprintf(stderr, "Stack is empty, cannot pop element\n");
    // exit(EXIT_FAILURE);
}