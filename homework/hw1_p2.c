#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100
#define HEAP_FULL(n) (n == MAX - 1)
#define HEAP_EMPTY(n) (!n)
#define MALLOC(p, s)\
    if(!((p) = malloc(s))){\
        fprintf(stderr, "Insufficient memory");\
        exit(EXIT_FAILURE);\
    }
int min_heap[MAX];
void push(int);
int pop();
int n = 0;

int main(){
    FILE *fileinput, *fileoutput;
    char fileinputname[] = "hw1_p2_input1.txt";
    char fileoutputname[] = "hw1_p2_output1.txt";
    fileinput = fopen(fileinputname, "r");
    fileoutput = fopen(fileoutputname, "w");
    if(fileinput == NULL || fileoutput == NULL){
        printf("Fail to open file\n");
        return 1;
    }

    int num;
    char step[10];
    while (fscanf(fileinput, "%s %d", step, &num) != EOF) {
        if(strcmp(step, "insert") == 0)
            push(num);
        else if(strcmp(step, "delete") == 0)
            pop();
    }
    for(int i = 1; i <= n; i++)
        fprintf(fileoutput, "%d ", min_heap[i]);

    fclose(fileinput);
    fclose(fileoutput);
    return 0;
}

void push(int item){
    if(HEAP_FULL(n)){
        fprintf(stderr, "The heap is full.\n");
        exit(EXIT_FAILURE);
    }
    int i = ++n;
    while((i != 1) && (item < min_heap[i/2])){
        min_heap[i] = min_heap[i/2];
        i /= 2;
    }
    min_heap[i] = item;
}

int pop(){
    if(HEAP_EMPTY(n)){
        fprintf(stderr, "The heap is empty.\n");
        exit(EXIT_FAILURE);
    }
    int parent = 1, child = 2;
    int item = min_heap[1], temp = min_heap[n--];
    while(child <= n){
        if((child < n) && (min_heap[child] > min_heap[child + 1]))
            child++;
        if(temp <= min_heap[child])
            break;
        min_heap[parent] = min_heap[child];
        parent = child;
        child *= 2;
    }
    min_heap[parent] = temp;
    return item;
}
