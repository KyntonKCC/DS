#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10
typedef struct {
    int key;
} Element;
Element array[MAX_SIZE] = {
    [0] = {.key = 26},
    [1] = {.key = 5},
    [2] = {.key = 37},
    [3] = {.key = 1},
    [4] = {.key = 61},
    [5] = {.key = 11},
    [6] = {.key = 59},
    [7] = {.key = 15},
    [8] = {.key = 48},
    [9] = {.key = 19},
};
void quickSort(Element *, int, int);
void printArray(Element *);

int main(){
    printArray(array);
    printf("-------------------------------\n");
    quickSort(array, 0, MAX_SIZE - 1);
    printArray(array);
    return 0;
}

void quickSort(Element * array, int left, int right){
    if(left < right){
        int i = left, j = right;
        Element pivot = array[left];
        printf("(%d,%d) %2d :\n", left, right, pivot.key);
        printArray(array);
        while(i < j){
            while(array[i].key <= pivot.key && i < right) i++;
            while(array[j].key >= pivot.key && left < j) j--;
            if(i < j){
                Element temp = array[i];
                array[i] = array[j];
                array[j] = temp;
                printArray(array);
            }
        }
        array[left] = array[j];
        array[j] = pivot;
        printArray(array);
        printf("-------------------------------\n");
        quickSort(array, left, j - 1);
        quickSort(array, j + 1, right);
    }
}

void printArray(Element * array){
    for(int i = 0; i < MAX_SIZE; i++)
        printf("%2d ", array[i].key);
    printf("\n");
}
