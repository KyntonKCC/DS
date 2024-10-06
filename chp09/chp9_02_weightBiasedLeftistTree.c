#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chp9_00_buildtree.h"
void HBLT(treePointer);
treePointer meldTree(treePointer, treePointer);
void WBLT(treePointer);

/*
          2                  __5__                  _2_                           ___2___
         / \                /     \                /   \                         /       \
        7   50             9       8              7   __5__                   __5__       7
       /    /             /       /     ->       /   /     \        ->       /     \     /
      11  80             12      10             11  9       8               8       9   11
     /                  /  \    /              /   /       / \             / \     /   /
    13                 20  18  15             13  12      10 50           10 50   12  13
                                                 /  \    /   /           /   /   /  \
                                                20  18  15  80          15  80  20  18


         1                  _3_                     _1_                          ___1___        
        / \                /   \                   /   \                        /       \   
      10   8              4     7                 10   _3_                    _3_       10      
      /   /              / \   /                 /    /   \                  /   \      /    
    12   11             6  20 10        ->      12   4     7        ->      4     7    12      
        /              / \   /                      / \   / \              / \   / \        
       16             25 21 15                     6  20 10  8            6  20 10  8      
                     /                            / \   /   /            / \   /   /         
                    27                           25 21 15  11           25 21 15  11        
                                                /         /            /         /            
                                               27        16           27        16     


        3               5                           __3__                           __3__
       / \             / \                         /     \                         /     \
      17  7           8   6                       17      5                       5      17        
       \   \           \   \            ->         \     / \        ->           / \     /                 
        22  15          11  9                       22  8   6                   8   6   22                  
           /               / \                           \   \                 /   /                   
          36              25 23                           11  7               11  7                        
                                                               \                 /                      
                                                                9               9                        
                                                               / \             / \                         
                                                              25 15           15 25                            
                                                                /  \         /  \                               
                                                               36  23       36  23                            
*/

int main(){
    char input1[MAX_SIZE] = "[2,7,50,11,null,80,null,13]";
    char input2[MAX_SIZE] = "[5,9,8,12,null,10,null,20,18,15]";
    // char input1[MAX_SIZE] = "[1,10,8,12,null,11,null,null,null,16]";
    // char input2[MAX_SIZE] = "[3,4,7,6,20,10,null,25,21,null,null,15,null,27]";
    // char input1[MAX_SIZE] = "[3,17,7,null,22,null,15,null,null,36]";
    // char input2[MAX_SIZE] = "[5,8,6,null,11,null,9,null,null,25,23]";
    treePointer root1 = buildTree(input1);
    reset();
    treePointer root2 = buildTree(input2);
    reset();
    treePointer root3 = meldTree(root1, root2);
    HBLT(root3);
    WBLT(root3);
    printTree(root3);
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

treePointer meldTree(treePointer root1, treePointer root2){
    if(root1 == NULL) return root2;
    if(root2 == NULL) return root1;
    treePointer head = root1->value < root2->value ? root1 : root2;
    head->rightChild = meldTree(head->rightChild, root1->value < root2->value ? root2 : root1);
    return head;
}

void WBLT(treePointer ptr){
    if(ptr->leftChild != NULL)
        WBLT(ptr->leftChild);
    if(ptr->rightChild != NULL)
        WBLT(ptr->rightChild);
    if((ptr->leftChild == NULL && ptr->rightChild != NULL) || 
            (ptr->leftChild != NULL && ptr->rightChild != NULL && ptr->leftChild->shortest < ptr->rightChild->shortest)){
        treePointer tempPtr;
        tempPtr = ptr->leftChild;
        ptr->leftChild = ptr->rightChild;
        ptr->rightChild = tempPtr;
    }
}