#include <stdio.h>
#define MAX_TERM 101
#define MAX_COL 101
typedef struct{
    int col;
    int row;
    int value;
} term;
void transpose(term [], term []);
void fastTranspose(term [], term []);
term a[MAX_TERM] = {
    [0] = {.col = 6, .row = 6, .value =   8,},
    [1] = {.col = 0, .row = 0, .value =  15,},
    [2] = {.col = 0, .row = 3, .value =  22,},
    [3] = {.col = 0, .row = 5, .value = -15,},
    [4] = {.col = 1, .row = 1, .value =  11,},
    [5] = {.col = 1, .row = 2, .value =   3,},
    [6] = {.col = 2, .row = 3, .value =  -6,},
    [7] = {.col = 4, .row = 0, .value =  91,},
    [8] = {.col = 5, .row = 2, .value =  28,},
};
term b[MAX_TERM];

int main(void){
    // transpose(a, b);
    fastTranspose(a, b);
    for(int i = 0; i < 9; i++)
        printf("%d\t%d\t%d\n", b[i].col, b[i].row, b[i].value);
    return 0;
}

void transpose(term a[], term b[]){
    int n = a[0].value;
    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = n;
    if(n > 0){          //non zero matrix
        int currentb = 1;
        for(int i = 0; i < b[0].row; i++){
            for(int j = 1; j <= n; j++){
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
    int j, rowTerms[MAX_COL], startintPos[MAX_COL];
    int numCols = a[0].col, numTerms = a[0].value;
    b[0].row = numCols;
    b[0].col = a[0].row;
    b[0].value = numTerms;
    if(numTerms > 0){       //non zero matrix
        for(int i = 0; i < numCols; i++)
            rowTerms[i] = 0;
        for(int i = 1; i <= numTerms; i++)
            rowTerms[a[i].col]++;
        startintPos[0] = 1;
        for(int i = 1; i < numCols; i++)
            startintPos[i] = startintPos[i - 1] + rowTerms[i - 1];
        for(int i = 1; i <= numTerms; i++){
            j = startintPos[a[i].col]++;
            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].value = a[j].value;
        }
    }
}