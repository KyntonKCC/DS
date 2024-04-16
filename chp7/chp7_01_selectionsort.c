#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 7
typedef struct {
    int key;
} Element;
Element array[MAX_SIZE] = {
    [0] = {.key = 44},
    [1] = {.key = 33},
    [2] = {.key = 22},
    [3] = {.key = 77},
    [4] = {.key = 66},
    [5] = {.key = 11},
    [6] = {.key = 55},
};
void selectionSort(Element *);
void printArray(Element *);

int main(){
    printArray(array);
    printf("-------------------\n");
    selectionSort(array);
    printArray(array);
    return 0;
}

void selectionSort(Element * array){
    for(int i = 0; i < MAX_SIZE; i++){
        int min = i;
        for(int j = i; j < MAX_SIZE; j++){
            if(array[j].key < array[min].key){
                min = j;
            }
        }
        Element temp = array[i];
        array[i] = array[min];
        array[min] = temp;
        printArray(array);
        printf("-------------------\n");
    }
}

void printArray(Element * array){
    for(int i = 0; i < MAX_SIZE; i++)
        printf("%2d ", array[i].key);
    printf("\n");
}
