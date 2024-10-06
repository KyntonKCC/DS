#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chp9_00_buildtree.h"
void HBLT(treePointer);

/*
          2                  __5__
         / \                /     \
        7   50             9       8
       /    /             /       /
      11  80             12      10
     /                  /  \    /
    13                 20  18  15

         1                  _3_
        / \                /   \
      10   8              4     7
      /   /              / \   / 
    12   11             6  20 10  
        /              / \   /
       16             25 21 15
                     /
                    27
*/

int main(){
    char input1[MAX_SIZE] = "[2,7,50,11,null,80,null,13]";
    char input2[MAX_SIZE] = "[5,9,8,12,null,10,null,20,18,15]";
    // char input1[MAX_SIZE] = "[1,10,8,12,null,11,null,null,null,16]";
    // char input2[MAX_SIZE] = "[3,4,7,6,20,10,null,25,21,null,null,15,null,27]";
    treePointer root1 = buildTree(input1);
    HBLT(root1);
    printTree(root1);
    reset();
    treePointer root2 = buildTree(input2);
    HBLT(root2);
    printTree(root2);
    reset();
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
