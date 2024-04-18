#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10
typedef struct {
    int key;
} Element;
Element array[MAX_SIZE] = {
    [0] = {.key = 26},
    [1] = {.key = 5},
    [2] = {.key = 77},
    [3] = {.key = 1},
    [4] = {.key = 61},
    [5] = {.key = 11},
    [6] = {.key = 59},
    [7] = {.key = 15},
    [8] = {.key = 48},
    [9] = {.key = 19},
};
void heapSort(Element *);
void heapify(Element *, int, int);
void printArray(Element *);

int main(){
    printArray(array);
    printf("-------------------------------\n");
    heapSort(array);
    printArray(array);
    return 0;
}

void heapify(Element * array, int size, int i){
    printf("-> %d(%d)\n", i, array[i].key);
    printArray(array);
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if(left < size && array[left].key > array[largest].key)
        largest = left;
    if(right < size && array[right].key > array[largest].key)
        largest = right;
    if(largest != i){
        printf("%d(%d)<->%d(%d) ", largest, array[largest].key, i, array[i].key);
        Element temp = array[largest];
        array[largest] = array[i];
        array[i] = temp;
        heapify(array, size, largest);
    }
}

void heapSort(Element * array){
    for(int i = MAX_SIZE / 2 - 1; i >= 0; i--)
        heapify(array, MAX_SIZE, i);
    printf("-------------------------------\n");
    for(int i = MAX_SIZE - 1; i >= 0; i--){
        printf("%d(%d)<->%d(%d) ", 0, array[0].key, i, array[i].key);
        Element temp = array[0];
        array[0] = array[i];
        array[i] = temp;
        heapify(array, i, 0);
        printf("-------------------------------\n");
    }
}

void printArray(Element * array){
    for(int i = 0; i < MAX_SIZE; i++)
        printf("%2d ", array[i].key);
    printf("\n");
}