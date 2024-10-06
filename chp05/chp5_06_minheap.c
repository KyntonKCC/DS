#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200
#define HEAP_FULL(n) (n == MAX_ELEMENT - 1)
#define HEAP_EMPTY(n) (!n)
#define MALLOC(p, s)\
    if(!((p) = malloc(s))){\
        fprintf(stderr, "Insufficient memory");\
        exit(EXIT_FAILURE);\
    }
typedef struct element_s {
    int key;
} element_t;
element_t heap[MAX_ELEMENT];
void push(element_t);
element_t pop();
void printheap();
int n = 0;

int main(void){
    element_t start[6];
    start[0].key = 2;
    start[1].key = 7;
    start[2].key = 4;
    start[3].key = 10;
    start[4].key = 8;
    start[5].key = 6;
    push(start[3]);
    printheap();
    push(start[5]);
    printheap();
    push(start[0]);
    printheap();
    push(start[4]);
    printheap();
    push(start[1]);
    printheap();
    push(start[2]);
    printheap();
    element_t insert1;
    insert1.key = 1;
    push(insert1);
    printheap();
    pop();
    printheap();
    pop();
    printheap();
    pop();
    printheap();
    return 0;
}

void push(element_t item){
    if(HEAP_FULL(n)){
        fprintf(stderr, "The heap is full.\n");
        exit(EXIT_FAILURE);
    }
    int i = ++n;
    while((i != 1) && (item.key < heap[i/2].key)){
        heap[i] = heap[i/2];
        i /= 2;
    }
    heap[i] = item;
}

element_t pop(){
    if(HEAP_EMPTY(n)){
        fprintf(stderr, "The heap is empty.\n");
        exit(EXIT_FAILURE);
    }
    int parent = 1, child = 2;
    element_t item = heap[1], temp = heap[n--];
    while(child <= n){
        if((child < n) && (heap[child].key > heap[child + 1].key))
            child++;
        if(temp.key <= heap[child].key)
            break;
        heap[parent] = heap[child];
        parent = child;
        child *= 2;
    }
    heap[parent] = temp;
    return item;
}


void printheap(){
    for(int i = 1; i <= n; i++)
        printf("%d ", heap[i].key);
    printf("\n");
}
