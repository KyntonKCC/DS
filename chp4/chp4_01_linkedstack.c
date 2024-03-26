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
stackPointer top[MAX_STACK];
void printStack();
void push(element);
element pop();
int high = -1;

int main(void){
    element number[9] = {11, 22, 33, 44, 55, 66, 77, 88, 99};
    element e;
    push(number[0]);
    push(number[1]);
    push(number[2]);
    printStack();
    e = pop();
    e = pop();
    printStack();
    push(number[3]);
    push(number[4]);
    push(number[5]);
    e = pop();
    e = pop();
    printStack();
    push(number[6]);
    push(number[7]);
    e = pop();
    push(number[8]);
    printStack();
    return 0;
}

void printStack(){
    printf("The stack contents : ");
    for(int i = 0; i <= high; i++)
        printf("%4d", top[i]->data.key);
    printf("\n");
}

void push(element item){
    stackPointer temp;
    MALLOC(temp, sizeof(stackPointer));
    temp->data = item;
    temp->link = top[++high];
    top[high] = temp;
}

element pop(){
    stackPointer temp = top[high];
    if(!temp){
        fprintf(stderr, "Stack is empty!!!\n");
        exit(EXIT_FAILURE);
    }
    element item = temp->data;
    top[high--] = temp->link;
    free(temp);
    return item;
}
