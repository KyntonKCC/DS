#include <stdio.h>
#include <time.h>
#include "chp1_00_selectionsort.h"
#define MAX_SIZE 1001

int main(void){
    int step = 10;
    int a[MAX_SIZE];
    double duration;

    printf("n\trepetitions\ttime\n");
    for(int n = 0; n <= 1000; n += step){
        long repetitions = 0;
        clock_t start = clock();
        do{
            repetitions++;
            for(int i = 0; i < n; i++){
                a[i] = n - i;
            }
            sort(a, n);
        }while(clock() - start < 1000);
        duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
        printf("%-6d\t%-9ld\t%f\n", n, repetitions, duration);
        if(n == 100)
            step = 100;
    }
    return 0;
}