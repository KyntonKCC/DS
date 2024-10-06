#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE_STACK 50
#define MALLOC(p, s)\
    if(!((p) = malloc(s))){\
        fprintf(stderr, "Insufficient memory");\
        exit(EXIT_FAILURE);\
    }
typedef struct node_s * treePointer;
typedef struct node_s {
    treePointer leftChild;
    char data;
    treePointer rightChild;
} node_t;
treePointer copy(treePointer);
int equal(treePointer, treePointer);
void inorder(treePointer);

int main(void){
    treePointer start1[9];
    for(int i = 0; i < 9; i++)
        MALLOC(start1[i], sizeof(treePointer));
    treePointer start2[9];
    for(int i = 0; i < 9; i++)
        MALLOC(start2[i], sizeof(treePointer));
    {start1[0]->leftChild = start1[1];
    start1[0]->data = '+';
    start1[0]->rightChild = start1[2];
    start1[1]->leftChild = start1[3];
    start1[1]->data = '*';
    start1[1]->rightChild = start1[4];
    start1[2]->data = 'E';
    start1[3]->leftChild = start1[5];
    start1[3]->data = '*';
    start1[3]->rightChild = start1[6];
    start1[4]->data = 'D';
    start1[5]->leftChild = start1[7];
    start1[5]->data = '/';
    start1[5]->rightChild = start1[8];
    start1[6]->data = 'C';
    start1[7]->data = 'A';
    start1[8]->data = 'B';};

    {start2[0]->leftChild = start2[1];
    start2[0]->data = '-';
    start2[0]->rightChild = start2[2];
    start2[1]->leftChild = start2[3];
    start2[1]->data = '+';
    start2[1]->rightChild = start2[4];
    start2[2]->leftChild = start2[5];
    start2[2]->data = '/';
    start2[2]->rightChild = start2[6];
    start2[3]->data = 'A';
    start2[4]->data = 'B';
    start2[5]->leftChild = start2[7];
    start2[5]->data = '*';
    start2[5]->rightChild = start2[8];
    start2[6]->data = 'E';
    start2[7]->data = 'C';
    start2[8]->data = 'D';};
    
    inorder(start1[0]);
    printf("\n");
    treePointer temp;
    temp = copy(start1[0]);
    inorder(temp);
    printf("\n");
    printf("%d %d\n", equal(start1[0], temp), equal(start1[0], start2[0]));
    return 0;
}

treePointer copy(treePointer original){
    treePointer temp;
    if(original){
        MALLOC(temp, sizeof(treePointer));
        temp->leftChild = copy(original->leftChild);
        temp->data = original->data;
        temp->rightChild = copy(original->rightChild);
        return temp;
    }
    return NULL;
}

int equal(treePointer first, treePointer second){
    return ((!first && !second) ||
            (first && second && 
                (first->data == second->data) && 
                equal(first->leftChild, second->leftChild) && 
                equal(first->rightChild, second->rightChild)));
}

void inorder(treePointer ptr){
    if(ptr){
        inorder(ptr->leftChild);
        printf("%c ", ptr->data);
        inorder(ptr->rightChild);
    }
}
