#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p, s)\
    if(!((p) = malloc(s))){\
        fprintf(stderr, "Insufficient memory");\
        exit(EXIT_FAILURE);\
    }
typedef struct listNode * listPointer;  
//define the alias of (struct listNode *) as (listPointer)
struct listNode{
    int data;
    listPointer link;
};
listPointer first, second, third;               //(struct listNode *)
// struct listNode * first, * second, * third;  //(listPointer)
listPointer create();
void printList(listPointer);
void insert(listPointer *, listPointer, int);           //起始值位址,插入值位址,插入值
void delete(listPointer *, listPointer, listPointer);   //起始值位址,刪除值前位址,刪除值位址

int main(void){
    MALLOC(first, sizeof(listPointer));
    MALLOC(second, sizeof(listPointer));
    MALLOC(third, sizeof(listPointer));
    // MALLOC(first, sizeof(* first));
    // MALLOC(second, sizeof(* second));
    // MALLOC(third, sizeof(* third));
    printList(create());
    insert(&first, third, 40);
    printList(first);
    delete(&first, first, second);
    printList(first);
    return 0;
}

listPointer create(){
    third->data = 30;
    third->link = NULL;
    second->data = 20;
    second->link = third;
    first->data = 10;
    first->link = second;
    return first;
}

void printList(listPointer first){
    printf("The list contents : ");
    for(; first; first = first->link)
        printf("%4d", first->data);
    printf("\n");
}

void insert(listPointer * first, listPointer x, int number){
    listPointer temp;
    MALLOC(temp, sizeof(listPointer));
    // struct listNode * temp;
    // MALLOC(temp, sizeof(* temp));
    temp->data = number;
    if(* first){
        temp->link = x->link;
        x->link = temp;
    }else{
        temp->link = NULL;
        * first = temp;
    }
}

void delete(listPointer * first, listPointer trail, listPointer x){
    if(trail)
        trail->link = x->link;
    else
        * first = (* first)->link;
    free(x);
}