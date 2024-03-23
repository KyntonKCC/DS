#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 180
#define ROW 12 
#define COL 15
typedef struct{
    int vert;
    int horiz;
}offsets;
typedef struct{
    int row;
    int col;
    int dir;
}element;
offsets move[8] = {
    [0] = {.vert = -1, .horiz =  0},
    [1] = {.vert = -1, .horiz =  1},
    [2] = {.vert =  0, .horiz =  1},
    [3] = {.vert =  1, .horiz =  1},
    [4] = {.vert =  1, .horiz =  0},
    [5] = {.vert =  1, .horiz = -1},
    [6] = {.vert =  0, .horiz = -1},
    [7] = {.vert = -1, .horiz = -1},
};
element stack[MAX_STACK_SIZE];
int maze[ROW][COL] = {
    {0,1,0,0,0,1,1,0,0,0,1,1,1,1,1},
    {1,0,0,0,1,1,0,1,1,1,0,0,1,1,1},
    {0,1,1,0,0,0,0,1,1,1,1,0,0,1,1},
    {1,1,0,1,1,1,1,0,1,1,0,1,1,0,0},
    {1,1,0,1,0,0,1,0,1,1,1,1,1,1,1},
    {0,0,1,1,0,1,1,1,0,1,0,0,1,0,1},
    {0,0,1,1,0,1,1,1,0,1,0,0,1,0,1},
    {0,1,1,1,1,0,0,1,1,1,1,1,1,1,1},
    {0,0,1,1,0,1,1,0,1,1,1,1,1,0,1},
    {1,1,0,0,0,1,1,0,1,1,0,0,0,0,0},
    {0,0,1,1,1,1,1,0,0,0,1,1,1,1,0},
    {0,1,0,0,1,1,1,1,1,0,1,1,1,1,0}
};
int mark[ROW + 2][COL + 2];
int top = -1;
void push(element);
element pop();
void stackFull();
element stackEmpty();
void path();

int main(void){
    for(int i = 0; i < ROW + 2; i++){
        for(int j = 0; j < COL + 2; j++)
            if(i == 0 || i == ROW + 1 || j == 0 || j == COL + 1)
                mark[i][j] = 1;
            else
                mark[i][j] = maze[i - 1][j - 1];
    }
    for(int i = 0; i < ROW + 2; i++){
        for(int j = 0; j < COL + 2; j++)
            printf("%d ", mark[i][j]);
        printf("\n");
    }
    path();
    return 0;
}

void path(){
    int row, col, nextRow, nextCol, dir, found = 0;
    element position;
    top = 0;
    mark[1][1] = 1;
    stack[0].row = 1;
    stack[0].col = 1;
    stack[0].dir = 0;
    while(top > -1 && !found){
        position = pop();
        row = position.row;
        col = position.col;
        dir = position.dir;
        while(dir < 8 && !found){
            nextRow = row + move[dir].vert;
            nextCol = col + move[dir].horiz;
            if(nextRow == (ROW - 1) && nextCol == (COL - 1)){
                found = 1;
            }else if(!mark[nextRow][nextCol]){
                mark[nextRow][nextCol] = 1;
                position.row = row;
                position.col = col;
                position.dir = ++dir;
                push(position);
                row = nextRow;
                col = nextCol;
                dir = 0;
            }else{
                dir++;
            }
        }
    }
    if(found){
        printf("The path is :\n");
        printf("row col\n");
        for(int i = 0; i <= top; i++)
            printf("%2d%5d\n", stack[i].row, stack[i].col);
        printf("%2d%5d\n", row, col);
    }else{
        printf("The maze does not have a path\n");
    }
}

void push(element item){
    if(top >= MAX_STACK_SIZE - 1)
        stackFull();
    else
        stack[++top] = item;
}

element pop(){
    if(top == -1){
        return stackEmpty();
    }else{
        return stack[top--];
    }
}

void stackFull(){
    fprintf(stderr, "Stack is full, cannot add element\n");
    // exit(EXIT_FAILURE);
}

element stackEmpty(){
    fprintf(stderr, "Stack is empty, cannot pop element\n");
    // exit(EXIT_FAILURE);
}