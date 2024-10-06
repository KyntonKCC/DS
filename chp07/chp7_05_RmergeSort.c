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
    [2] = {.key = 5},
    [3] = {.key = 61},
    [4] = {.key = 1},
    [5] = {.key = 59},
    [6] = {.key = 11},
    [7] = {.key = 15},
    [8] = {.key = 48},
    [9] = {.key = 19},
};
void RmergeSort(Element *, int, int);
void Rmerge(Element *, int, int, int);
void printArray(Element *);

int main(){
    printArray(array);
    printf("-------------------------------\n");
    RmergeSort(array, 0, MAX_SIZE - 1);
    printArray(array);
    return 0;
}

void RmergeSort(Element * array, int left, int right){
    if(left < right){
        int mid = (left + right) / 2;
        RmergeSort(array, left, mid);
        RmergeSort(array, mid + 1, right);

        Rmerge(array, left, mid, right);
    }
}

void Rmerge(Element * array, int left, int mid, int right){
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