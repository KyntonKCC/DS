#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "chp10_01_opitmalBST.h"
typedef struct subset_s * Subset;
typedef struct subset_s {
    int w;
    int c;
    int r;
} subset_t;
typedef struct table_s * Table;
typedef struct table_s {
    int N;
    Subset ** Array;
} table_t;
Table createTable(int, int *);
Subset ** makeArray(int, int *);
int KnuthMin(Table, int, int);
void OBST(Table, int *, int *, int);
treePointer createTreePointer(int);
treePointer createTree(Table, int *, int, int);
void printArray(Table, int);

int main(){
    int n = 4;
    int a[] = {10, 15, 20, 25};
    int p[] = {3, 3, 1, 1};
    int q[] = {2, 3, 1, 1, 1};
    // int n = 7;
    // int a[] = {1, 2, 3, 4, 5, 6, 7};
    // int p[] = {5, 2, 3, 1, 4, 1, 2};
    // int q[] = {2, 4, 3, 1, 3, 1, 4, 3};
    Table table = createTable(n, q);
    OBST(table, p, q, n);
    treePointer root = createTree(table, a, 0, n);
    printArray(table, n);
    printTree(root);
    return 0;
}

Table createTable(int n, int * q){
    Table table;
    MALLOC(table, sizeof(* table));
    table->N = n;
    table->Array = makeArray(n, q);
    return table;
}

Subset ** makeArray(int n, int * q){
    n += 1;
    Subset ** array;
    MALLOC(array, n * sizeof(* array));
    for(int i = 0; i < n; i++){
        MALLOC(array[i], n * sizeof(* array[i]));
        for(int j = i; j < n; j++){
            MALLOC(array[i][j], sizeof(* array[i][j]));
            if(i == j)
                array[i][j]->w = q[i];
            else
                array[i][j]->w = 0;
            array[i][j]->c = 0;
            array[i][j]->r = 0;
        }
    }
    return array;
}

int KnuthMin(Table table, int i, int j) {
    int minCost = INT_MAX;
    int minK = i + 1;
    for (int k = i + 1; k <= j; k++) {
        int cost = table->Array[i][k - 1]->c + table->Array[k][j]->c;
        if (cost < minCost) {
            minCost = cost;
            minK = k;
        }
    }
    return minK;
}

void OBST(Table table, int * p, int * q, int n){
    for(int m = 1; m < (n + 1); m++){
        for(int i = 0; i < (n + 1) - m; i++){
            int j = i + m; 
            table->Array[i][j]->w = table->Array[i][j - 1]->w + p[j - 1] + q[j];
            int k = KnuthMin(table, i, j);
            table->Array[i][j]->c = table->Array[i][j]->w + table->Array[i][k - 1]->c + table->Array[k][j]->c;
            table->Array[i][j]->r = k;
        }
    }
}

treePointer createTreePointer(int num){
    treePointer newPointer;
    MALLOC(newPointer, sizeof(* newPointer));
    newPointer->leftChild = NULL;
    newPointer->key = num;
    newPointer->rightChild = NULL;
    return newPointer;
}

treePointer createTree(Table table, int * a, int m, int n){
    int r = table->Array[m][n]->r;
    treePointer ptr = createTreePointer(a[r - 1]);
    if(m != r - 1)
        ptr->leftChild = createTree(table, a, m, r - 1);
    if(r != n)
        ptr->rightChild = createTree(table, a, r, n);
    return ptr;
}

void printArray(Table table, int n){
    n += 1;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n - i; j++)
            printf("%3d ", table->Array[0 + j][i + j]->w);
        printf("\n");
        for(int j = 0; j < n - i; j++)
            printf("%3d ", table->Array[0 + j][i + j]->c);
        printf("\n");
        for(int j = 0; j < n - i; j++)
            printf("%3d ", table->Array[0 + j][i + j]->r);
        printf("\n");
    }
}