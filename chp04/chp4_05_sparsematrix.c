#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>
#define MALLOC(p, s)\
    if(!((p) = malloc(s))){\
        fprintf(stderr, "Insufficient memory");\
        exit(EXIT_FAILURE);\
    }
#define MAX_SIZE 50
typedef enum {
    head, entry
} tagfield;
typedef struct entryNode_s {
    int row;
    int col;
    int value;
} entryNode_t;
typedef struct matrixNode_s * matrixPointer;
typedef struct matrixNode_s {
    matrixPointer down;
    matrixPointer right;
    tagfield tag;
    union {
        matrixPointer next;
        entryNode_t entry;
    } u;
} matrixNode_t;
matrixPointer hdnode[MAX_SIZE];
matrixPointer mread();
void mwrite(matrixPointer);

int main(void){
    mwrite(mread());
    return 0;
}

matrixPointer mread(){                          //????
    int numRows, numCols, numTerms, numHeads;
    int row, col, value, currentRow;
    matrixPointer temp, last, node;
    printf("Enter the number of rows, columns and number of nonzero terms : ");
    scanf("%d %d %d", &numRows, &numCols, &numTerms);
    numHeads = (numCols > numRows) ? numCols : numRows;
    node = newNode();
    node->tag = entry;
    node->u.entry.row = numRows;
    node->u.entry.col = numCols;
    if(!numHeads){
        node->right = node;
    }else{
        for(int i = 0; i < numHeads; i++){
            temp = newNode();
            hdnode[i] = temp;
            hdnode[i]->tag = head;
            hdnode[i]->right = temp;
            hdnode[i]->u.next = temp;
        }
        currentRow = 0;
        last = hdnode[0];
        for(int i = 0; i < numTerms; i++){
            printf("Enter row, column and value : ");
            scanf("%d %d %d", &row, &col, &value);
            if(row > currentRow){
                last->right = hdnode[currentRow];
                currentRow = row;
                last = hdnode[row];
            }
            MALLOC(temp, sizeof(matrixPointer));
            temp->tag = entry;
            temp->u.entry.row = row;
            temp->u.entry.col = col;
            temp->u.entry.value = value;
            last->right = temp;
            last = temp;
            hdnode[col]->u.next->down = temp;
            hdnode[col]->u.next = temp;
        }
        last->right = hdnode[currentRow];
        for(int i = 0; i < numCols; i++){
            hdnode[i]->u.next->down = hdnode[i];
        }
        for(int i = 0; i < numHeads - 1; i++){
            hdnode[i]->u.next = hdnode[i + 1];
        }
        hdnode[numHeads - 1]->u.next = node;
        node->right = hdnode[0];
    }
    return node;
}

void mwrite(matrixPointer node){
    matrixPointer temp, head;
    head = node->right;
    printf("\nnumRows = %d, numCols = %d\n", node->u.entry.row, node->u.entry.col);
    printf("The matrix by row, column, and value : \n\n");
    for(int i = 0; i < node->u.entry.row; i++){
        for(temp = head->right; temp != head; temp = temp->right)
            printf("%5d%5d%5d\n", temp->u.entry.row, temp->u.entry.col, temp->u.entry.value);
        head = head->u.next;
    }
}