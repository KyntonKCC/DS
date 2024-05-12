#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chp9_00_buildtree.h"
#define MIN(a, b) ((a) < (b) ? (a) : (b))
void HBLT(treePointer);
void inorder2(treePointer);     //LVR
void preorder2(treePointer);    //VLR
void postorder2(treePointer);   //LRV

int main(){
    // char input[MAX_SIZE] = "[2,7,50,11,null,80,null,13]";
    // char input[MAX_SIZE] = "[5,9,8,12,null,10,null,20,18,15]";
    char input[MAX_SIZE] = "[6,8,7,20,null,null,11,null,5,null,13,12,14,9]";
    treePointer root = buildTree(input);
    HBLT(root);
    printf("------------Recursive Traversals------------");
    printf("\nPreorder:\t");
    preorder1(root);
    printf("\nShortest:\t");
    preorder2(root);
    printf("\nInorder:\t");
    inorder1(root);
    printf("\nShortest:\t");
    inorder2(root);
    printf("\nPostorder:\t");
    postorder1(root);
    printf("\nShortest:\t");
    postorder2(root);
    printf("\n");
    return 0;
}

void HBLT(treePointer ptr){
    if(ptr->leftChild != NULL)
        HBLT(ptr->leftChild);
    if(ptr->rightChild != NULL)
        HBLT(ptr->rightChild);
    if(ptr->leftChild == NULL || ptr->rightChild == NULL)
        ptr->shortest = 1;
    else
        ptr->shortest = MIN(ptr->leftChild->shortest, ptr->rightChild->shortest) + 1;
}

void inorder2(treePointer ptr) {
    if (ptr) {
        inorder2(ptr->leftChild);
        printf("%2d ", ptr->shortest);
        inorder2(ptr->rightChild);
    }
}

void preorder2(treePointer ptr) {
    if (ptr) {
        printf("%2d ", ptr->shortest);
        preorder2(ptr->leftChild);
        preorder2(ptr->rightChild);
    }
}

void postorder2(treePointer ptr) {
    if (ptr) {
        postorder2(ptr->leftChild);
        postorder2(ptr->rightChild);
        printf("%2d ", ptr->shortest);
    }
}