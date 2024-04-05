//chp2_02_sparsematrix
#include <stdio.h>
#define MAX_TERM 101
typedef struct{
    int col;
    int row;
    int value;
} term;
void fastTranspose(term [], term []);

int main(void){
    int R, C, T;
    scanf("%d %d %d", &R, &C, &T);
    term a[T+1], b[T+1];
    a[0].row = R;
    a[0].col = C;
    a[0].value = T;
    for (int i = 1; i <= T; i++) {
        int r, c, v;
        scanf("%d %d %d", &r, &c, &v);
        a[i].row = r;
        a[i].col = c;
        a[i].value = v;
    }
    fastTranspose(a, b);
    for(int i = 0; i <= T; i++)
        printf("%d\t%d\t%d\n", b[i].row, b[i].col, b[i].value);
    return 0;
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

        // printf("   rowTerms = ");
        // for(int i = 0; i < b[0].row; i++)
        //     printf("%d ", rowTerms[i]);
        // printf("\n");
        // printf("startingPos = ");
        // for(int i = 0; i <= b[0].row; i++)
        //     printf("%d ", startintPos[i]);
        // printf("\n");

        for(int i = 1; i <= b[0].value; i++){
            int j = ++startintPos[a[i].col];
            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].value = a[i].value;
        }
    }
}