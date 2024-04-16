#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 7
typedef struct {
    int key;
} Element;
Element array[MAX_SIZE] = {
    [0] = {.key = 77},
    [1] = {.key = 22},
    [2] = {.key = 44},
    [3] = {.key = 33},
    [4] = {.key = 66},
    [5] = {.key = 55},
    [6] = {.key = 11},
};
void insertionSort(Element *);
void printArray(Element *);

int main(){
    printArray(array);
    printf("-------------------\n");
    insertionSort(array);
    printArray(array);
    return 0;
}

void insertionSort(Element * array){
    for(int i = 1; i < MAX_SIZE; i++){
        Element temp = array[i];
        printf("%2d :\n", temp.key);
        int j = i - 1;
        while(temp.key < array[j].key && j >= 0){
            array[j + 1] = array[j];
            printArray(array);
            j--;
        }
        array[j + 1] = temp;
        printArray(array);
        printf("-------------------\n");
    }
}

void printArray(Element * array){
    for(int i = 0; i < MAX_SIZE; i++)
        printf("%2d ", array[i].key);
    printf("\n");
}
