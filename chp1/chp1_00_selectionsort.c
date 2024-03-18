#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "chp1_00_selectionsort.h"
#define MAX_SIZE 101
// #define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
// void sort(int[], int);

int main(void){
    int n;
    // int list[MAX_SIZE];
    printf("Enter the number of numbers to generate: ");
    scanf("%d", &n);
    if(n < 1 || n > MAX_SIZE){
        fprintf(stderr, "Improper value of n\n");
        exit(EXIT_FAILURE);
    }
    int * list = malloc(n * sizeof(int));
    srand(time(NULL));
    for(int i = 0; i < n; i++){ //randomly generate numbers
        list[i] = rand() % 1000;
        printf("%d ", list[i]);
    }
    sort(list, n);
    printf("\nSorted array:\n");
    for(int i = 0; i < n; i++){ //print out sorted numbers
        printf("%d ", list[i]);
    }
    printf("\n");
    return 0;
}

// void sort(int list[], int n){
//     int min, tmp;
//     for(int i = 0; i < n - 1; i++){
//         min = i;
//         for(int j = i + 1; j < n; j++){
//             if(list[j] < list[min]){
//                 min = j;
//             }
//         }
//         SWAP(list[i], list[min], tmp);
//     }
// }