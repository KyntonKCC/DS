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
    [6] = {.key = 55},
    [5] = {.key = 11},
};
void bubbleSort(Element *);
void printArray(Element *);

int main(){
    printArray(array);
    printf("----------------------\n");
    bubbleSort(array);
    printArray(array);
    return 0;
}

void bubbleSort(Element * array){
    for(int i = 0; i < MAX_SIZE - 1; i++){
        for(int j = 0; j < MAX_SIZE - 1 - i; j++){
            if(array[j].key > array[j + 1].key){
                Element temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
            printArray(array);
        }
        printf("----------------------\n");
    }
}

void printArray(Element * array){
    for(int i = 0; i < MAX_SIZE; i++)
        printf("%2d ", array[i].key);
    printf("\n");
}
