#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10
#define MIN(a, b) ((a) < (b) ? (a) : (b)) 
typedef struct {
    int key;
} Element;
Element array[MAX_SIZE] = {
    [0] = {.key = 77},
    [1] = {.key = 26},
    [2] = {.key = 61},
    [3] = {.key = 5},
    [4] = {.key = 59},
    [5] = {.key = 1},
    [6] = {.key = 15},
    [7] = {.key = 11},
    [8] = {.key = 48},
    [9] = {.key = 19},
};
void ImergeSort(Element *);
void Imerge(Element *, int, int, int);
void printArray(Element *);

int main(){
    printArray(array);
    printf("-------------------------------\n");
    ImergeSort(array);
    printArray(array);
    return 0;
}

void ImergeSort(Element * array){
    // int currSize = 1;
    // while(currSize < MAX_SIZE){
    //     int left = 0;
    //     while(left < MAX_SIZE - 1){
    //         int mid = MIN(left + currSize - 1, MAX_SIZE - 1);
    //         // printf("%d %d\n", left + currSize - 1, MAX_SIZE - 1);
    //         int right = MIN(left + 2 * currSize - 1, MAX_SIZE - 1);
    //         // printf("%d %d\n", left + 2 * currSize - 1, MAX_SIZE - 1);
    //         Imerge(array, left, mid, right);
    //         left = left + 2 * currSize;
    //     }
    //     currSize = 2 * currSize;
    // }
    for(int currSize = 1; currSize < MAX_SIZE; currSize *= 2){
        for(int left = 0; left < MAX_SIZE - 1; left += (2 * currSize)){
            int mid = MIN(left + currSize - 1, MAX_SIZE - 1);
            int right = MIN(left + 2 * currSize - 1, MAX_SIZE - 1);
            Imerge(array, left, mid, right);
        }
    }
}

void Imerge(Element * array, int left, int mid, int right){
    int num1 = mid + 1 - left;
    int num2 = right - mid;
    printf("(%d,%d,%d),", left, mid, right);
    printf("(%d,%d)\n", num1, num2);
    Element L[num1], R[num2];
    for(int i = 0; i < num1; i++)
        L[i] = array[left + i];
    for(int j = 0; j < num2; j++)
        R[j] = array[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while(i < num1 && j < num2){
        if(L[i].key <= R[j].key)
            array[k++] = L[i++];
        else
            array[k++] = R[j++];
    }
    while(i < num1) array[k++] = L[i++];
    while(j < num2) array[k++] = R[j++];
    printArray(array);
    printf("-------------------------------\n");
}

void printArray(Element * array){
    for(int i = 0; i < MAX_SIZE; i++)
        printf("%2d ", array[i].key);
    printf("\n");
}