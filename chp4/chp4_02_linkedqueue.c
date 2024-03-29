#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE 10
#define MALLOC(p, s)\
    if(!((p) = malloc(s))){\
        fprintf(stderr, "Insufficient memory");\
        exit(EXIT_FAILURE);\
    }
typedef struct{
    int key;
}element;
typedef struct queue * queuePointer;
struct queue{
    element data;
    queuePointer link;
};
queuePointer start, end;
void printQueue(queuePointer);
void addq(element);
element deleteq();

int main(void){
    MALLOC(end, sizeof(queuePointer));
    start = end;
    element number[9] = {11, 22, 33, 44, 55, 66, 77, 88, 99};
    element e;
    {addq(number[0]);
    addq(number[1]);
    addq(number[2]);
    e = deleteq();
    e = deleteq();
    e = deleteq();
    // e = deleteq();
    addq(number[3]);
    addq(number[4]);
    addq(number[5]);
    e = deleteq();
    e = deleteq();
    addq(number[6]);
    addq(number[7]);
    e = deleteq();
    addq(number[8]);};
    return 0;
}

void printQueue(queuePointer start){
    printf("The queue contents : ");
    for(; start; start = start->link)
        printf("%4d", start->data.key);
    printf("\n");
}

void addq(element item){
    queuePointer temp;
    MALLOC(temp, sizeof(queuePointer));
    temp->data = item;
    temp->link = NULL;
    end->link = temp;
    end = end->link;
    printQueue(start->link);
}

element deleteq(){
    queuePointer temp = start->link;
    if(!temp){
        fprintf(stderr, "Queue is empty!!!\n");
        exit(EXIT_FAILURE);
    }
    element item = temp->data;
    if(temp->link != NULL){
        start->link = temp->link;
    }else{
        MALLOC(end, sizeof(queuePointer));
        start = end;
    }
    free(temp);
    printf("delete : %d\n", item.key);
    printQueue(start->link);
    return item;
}