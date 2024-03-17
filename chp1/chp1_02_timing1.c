#include <stdio.h>
#include <time.h>
#include "chp1_00_selectionsort.h"
#define MAX_SIZE 1001

int main(void){
    int step = 10;
    int a[MAX_SIZE];
    double duration;
    clock_t start;

    printf("n\ttime\n");
    for(int n = 0; n <= 1000; n += step){
        for(int i = 0; i < n; i++){
            a[i] = n - i;
        }
        start = clock();
        sort(a, n);
        duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
        printf("%-6d\t%f\n", n, duration);
        if(n == 100)
            step = 100;
    }
    return 0;
}