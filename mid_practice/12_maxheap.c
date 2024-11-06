#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100
#define HEAP_FULL(n) (n == MAX - 1)
#define HEAP_EMPTY(n) (!n)
int max_heap[MAX];
void insert(int);
void delete(int);
int n = 0;

int main(){
    int num;
    char step[50];
    while (scanf("%s %d", step, &num) != EOF) {
        if(strcmp(step, "insert") == 0)
            insert(num);
        else if(strcmp(step, "delete") == 0)
            delete(num);
    }
    for(int i = 1; i <= n; i++)
        printf("%d ", max_heap[i]);
    printf("\n");

    return 0;
}

void insert(int item){
    if(HEAP_FULL(n)){
        fprintf(stderr, "The heap is full.\n");
        exit(EXIT_FAILURE);
    }
    int i = ++n;
    while((i != 1) && (item > max_heap[i/2])){
        max_heap[i] = max_heap[i/2];
        i /= 2;
    }
    max_heap[i] = item;
}

void delete(int num){
    if(HEAP_EMPTY(n)){
        fprintf(stderr, "The heap is empty.\n");
        exit(EXIT_FAILURE);
    }

    int i, parent, child, temp = max_heap[n--];
    for(i = 1; i <= n; i++) 
        if(max_heap[i] == num) 
            break;
    parent = i;
    

    while(parent * 2 <= n){
        child = parent * 2;
        if((child < n) && (max_heap[child] < max_heap[child + 1]))
            child++;
        if(temp >= max_heap[child])
            break;
        max_heap[parent] = max_heap[child];
        parent = child;
    }
    max_heap[parent] = temp;
}