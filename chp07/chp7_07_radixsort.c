#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10
typedef struct {
    int key;
} Element;
Element array[MAX_SIZE] = {
    [0] = {.key = 179},
    [1] = {.key = 208},
    [2] = {.key = 306},
    [3] = {.key = 93},
    [4] = {.key = 859},
    [5] = {.key = 984},
    [6] = {.key = 55},
    [7] = {.key = 9},
    [8] = {.key = 271},
    [9] = {.key = 33},
};
void radixSort(Element *);
void printArray(Element *);

int main(){
    printArray(array);
    printf("------------------------------------------\n");
    radixSort(array);
    printArray(array);
    return 0;
}

void radixSort(Element * array){
    Element temp[MAX_SIZE];
    int digit = 1;
    int largest = array[0].key;
    for(int i = 0; i < MAX_SIZE; i++)
        if(array[i].key > largest)
            largest = array[i].key;
    while(largest / digit > 0){
        int bucket[10] = {0};
        for(int i = 0; i < MAX_SIZE; i++)
            bucket[(array[i].key / digit) % 10]++;
        for(int i = 0; i < 10; i++)
            printf("%3d ", bucket[i]);
        printf("\n");
        for(int i = 1; i < 10; i++)
            bucket[i] += bucket[i - 1];
        for(int i = 0; i < 10; i++)
            printf("%3d ", bucket[i]);
        printf("\n");
        for(int i = MAX_SIZE - 1; i >= 0; i--)
            temp[--bucket[(array[i].key / digit) % 10]] = array[i];
        for(int i = 0; i < MAX_SIZE; i++)
            array[i] = temp[i];
        digit *= 10;
        printArray(array);
        printf("------------------------------------------\n");
    }
}

void printArray(Element * array){
    for(int i = 0; i < MAX_SIZE; i++)
        printf("%3d ", array[i].key);
    printf("\n");
}