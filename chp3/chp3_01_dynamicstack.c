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
element * stack;
int capacity = 1;
int top = -1;
void push(element);
element pop();
void stackFull();
element stackEmpty();

int main(void){
    MALLOC(stack, sizeof(* stack));
    element item[8];
    for(int i = 0; i < 8; i++)
        item[i].key = i+1;
    // for(int i = 0; i < capacity; i++)
    //     printf("%d ", stack[i].key);
    // printf("\n");
    for(int i = 0; i < 8; i++)
        push(item[i]);
    // for(int i = 0; i < capacity; i++)
    //     printf("%d ", stack[i].key);
    // printf("\n");
    for(int i = 0; i < 9; i++){
        element e = pop();
    }
    // for(int i = 0; i < capacity; i++)
    //     printf("%d ", stack[i].key);
    // printf("\n");
    return 0;
}

void push(element item){
    if(top >= capacity - 1)
        stackFull();
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
    printf("Stack is full, cannot add element, capacity = %d\n", capacity);
    REALLOC(stack, 2 * capacity * sizeof(* stack));
    capacity *= 2;
}

element stackEmpty(){
    fprintf(stderr, "Stack is empty, cannot pop element\n");
    // exit(EXIT_FAILURE);
}
