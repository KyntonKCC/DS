#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p,s)\
    if(!((p) = malloc(s))){\
        fprintf(stderr, "Insufficient memory");\
        exit(EXIT_FAILURE);\
    }

int **make2dArray(int, int);
int main(void){
    int **myArray;
    myArray = make2dArray(5, 10);
    myArray[2][4] = 7;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 10; j++){
            printf("%d ", myArray[i][j]);
        }
        printf("\n");
    }
    return 0;
}

int **make2dArray(int rows, int cols){
    //1.
    // int **x = NULL;
    // x = (int **)malloc(rows * sizeof(int *));
    // for(int i = 0; i < rows; i++)
    //     x[i] = (int *)malloc(cols * sizeof(int));

    //2.
    // int **x;
    // x = malloc(rows * sizeof(*x));
    // for(int i = 0; i < rows; i++)
    //     x[i] = malloc(cols * sizeof(**x));

    //3.
    int **x;
    MALLOC(x, rows * sizeof(*x));
    for(int i = 0; i < rows; i++)
        MALLOC(x[i], cols * sizeof(**x));
    
    return x;
}