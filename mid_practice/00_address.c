#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p, s) \
    if(!((p) = malloc(s))){ \
        printf("Insufficient memory"); \
        exit(EXIT_FAILURE); \
    }
int **make2dArray(int, int);

int main(void){
    int **myArray;
    myArray = make2dArray(7, 9);
    myArray[4][7] = 6;
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 9; j++)
            printf("%d ", myArray[i][j]);
        printf("\n");
    }
    return 0;
}

int **make2dArray(int rows, int cols){
    int **Array;
    MALLOC(Array, rows * sizeof(*Array));
    for(int i = 0; i < rows; i++)
        MALLOC(Array[i], cols * sizeof(**Array));
    return Array;
}