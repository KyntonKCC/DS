#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK 10
#define MALLOC(p, s)\
    if(!((p) = malloc(s))){\
        fprintf(stderr, "Insufficient memory");\
        exit(EXIT_FAILURE);\
    }
typedef struct{
    int key;
}element;
typedef struct stack * stackPointer;
struct stack{
    element data;
    stackPointer link;
};
stackPointer start, end;
void printStack(stackPointer);
void push(element);
element pop();

int main(void){
    MALLOC(end, sizeof(stackPointer));
    start = end;
    element number[9] = {11, 22, 33, 44, 55, 66, 77, 88, 99};
    element e;
    {push(number[0]);
    push(number[1]);
    push(number[2]);
    e = pop();
    e = pop();
    e = pop();
    // e = pop();
    push(number[3]);
    push(number[4]);
    push(number[5]);
    e = pop();
    e = pop();
    push(number[6]);
    push(number[7]);
    e = pop();
    push(number[8]);};
    return 0;
}

void printStack(stackPointer start){
    printf("The stack contents : ");
    for(; start; start = start->link)
        printf("%4d", start->data.key);
    printf("\n");
}

void push(element item){
    stackPointer temp;
    MALLOC(temp, sizeof(stackPointer));
    temp->data = item;
    temp->link = NULL;
    end->link = temp;
    end = end->link;
    printStack(start->link);
}

element pop(){
    stackPointer temp = end;
    stackPointer pass = start;
    if(!pass->link){
        fprintf(stderr, "Stack is empty!!!\n");
        exit(EXIT_FAILURE);
    }
    for(; pass->link != temp; pass = pass->link);
    element item = temp->data;
    pass->link = NULL;
    end = pass;
    free(temp);
    printf("pop out : %d\n", item.key);
    printStack(start->link);
    return item;
}