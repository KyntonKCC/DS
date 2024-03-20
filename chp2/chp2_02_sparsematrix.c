#include <stdio.h>
#define MAX_TERM 101
typedef struct{
    int col;
    int row;
    int value;
} term;
void transpose(term [], term []);
void fastTranspose(term [], term []);
term a[MAX_TERM] = {
    [0] = {.row = 6, .col = 6, .value =   8,},
    [1] = {.row = 0, .col = 0, .value =  15,},
    [2] = {.row = 0, .col = 3, .value =  22,},
    [3] = {.row = 0, .col = 5, .value = -15,},
    [4] = {.row = 1, .col = 1, .value =  11,},
    [5] = {.row = 1, .col = 2, .value =   3,},
    [6] = {.row = 2, .col = 3, .value =  -6,},
    [7] = {.row = 4, .col = 0, .value =  91,},
    [8] = {.row = 5, .col = 2, .value =  28,},
};
term b[MAX_TERM];
term c[MAX_TERM];

int main(void){
    transpose(a, b);
    printf("=====transpose=====\n");
    for(int i = 0; i < 9; i++)
        printf("%d\t%d\t%d\n", b[i].row, b[i].col, b[i].value);
    printf("===fastTranspose===\n");
    fastTranspose(a, c);
    for(int i = 0; i < 9; i++)
        printf("%d\t%d\t%d\n", c[i].row, c[i].col, c[i].value);
    return 0;
}

void transpose(term a[], term b[]){
    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = a[0].value;
    if(b[0].value > 0){             //non zero matrix
        int currentb = 1;
        for(int i = 0; i < b[0].row; i++){
            for(int j = 1; j <= b[0].value; j++){
                if(a[j].col == i){
                    b[currentb].row = a[j].col;
                    b[currentb].col = a[j].row;
                    b[currentb].value = a[j].value;
                    currentb++;
                }
            }
        }
    }
}

void fastTranspose(term a[], term b[]){
    int rowTerms[MAX_TERM], startintPos[MAX_TERM];
    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = a[0].value;
    if(b[0].value > 0){             //non zero matrix
        for(int i = 0; i < b[0].row; i++)
            rowTerms[i] = 0;
        for(int i = 1; i <= b[0].value; i++)
            rowTerms[a[i].col]++;
        startintPos[0] = 0;
        for(int i = 1; i <= b[0].row; i++)
            startintPos[i] = startintPos[i - 1] + rowTerms[i - 1];

        printf("   rowTerms = ");
        for(int i = 0; i < b[0].row; i++)
            printf("%d ", rowTerms[i]);
        printf("\n");
        printf("startingPos = ");
        for(int i = 0; i <= b[0].row; i++)
            printf("%d ", startintPos[i]);
        printf("\n");

        for(int i = 1; i <= b[0].value; i++){
            int j = ++startintPos[a[i].col];
            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].value = a[i].value;
        }
    }
}