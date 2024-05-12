#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chp9_00_buildtree.h"

int main(){
    // char input[MAX_SIZE] = "[2,7,50,11,null,80,null,13]";
    // char input[MAX_SIZE] = "[5,9,8,12,null,10,null,20,18,15]";
    char input[MAX_SIZE] = "[6,8,7,20,null,null,11,null,5,null,13,12,14,9]";
    treePointer root = buildTree(input);

    printf("------------Recursive Traversals------------");
    printf("\nPreorder:\t");
    preorder1(root);
    printf("\nInorder:\t");
    inorder1(root);
    printf("\nPostorder:\t");
    postorder1(root);
    printf("\n");
    return 0;
}