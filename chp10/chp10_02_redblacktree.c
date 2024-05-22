#include <stdio.h>
#include <stdlib.h>
#include "chp10_02_redblacktree.h"
treePointer createTreePointer(treePointer, treePointer, int);
treePointer insert(treePointer, int);
treePointer insertRB(treePointer, treePointer, int);
treePointer calRB(treePointer);
treePointer RBT_CC_R(treePointer);
treePointer RBT_CC_B(treePointer);
treePointer RBT_LL_B(treePointer);
treePointer RBT_LR_B(treePointer);
treePointer RBT_RR_B(treePointer);
treePointer RBT_RL_B(treePointer);
/*
    LL_R:                                   RR_R:
    
            G_B                  G_R            G_B                  G_R
           /   \                /   \          /   \                /   \
        P_R     U_R   --->   P_B     U_B    U_R     P_R   --->   U_B     P_B
       /                    /                          \                    \
    S_R                  S_R                            S_R                  S_R

    LR_R:                                   RL_R:
    
            G_B                  G_R            G_B                  G_R
           /   \                /   \          /   \                /   \
        P_R     U_R   --->   P_B     U_B    U_R     P_R   --->   U_B     P_B
           \                    \                  /                    /    
            S_R                  S_R            S_R                  S_R    

    LR_B:                   LL_B:

            G_B                  G_B                  S_B
           /   \                /   \                /   \
        P_R     U_B   --->   S_R     U_B   --->   P_R     G_R
           \                /                                \
            S_R          P_R                                  U_B

    RL_B:                   RR_B:

            G_B                  G_B                  S_B
           /   \                /   \                /   \
        U_B     P_R   --->   U_B     S_R   --->   G_R     P_R
               /                        \        /             
            S_R                          P_R  U_B                
*/
int main(){
    treePointer root = NULL;
    root = insert(root, 10);
    root = calRB(root);
    // printTree(root);
    root = insert(root, 50);
    root = calRB(root);
    // printTree(root);
    root = insert(root, 80);
    root = calRB(root);
    // printTree(root);
    root = insert(root, 90);
    root = calRB(root);
    // printTree(root);
    root = insert(root, 70);
    root = calRB(root);
    // printTree(root);
    root = insert(root, 60);
    root = calRB(root);
    // printTree(root);
    root = insert(root, 65);
    root = calRB(root);
    // printTree(root);
    root = insert(root, 62);
    root = calRB(root);
    printTree(root);
    // treePointer root = NULL;
    // root = insert(root, 12);
    // root = calRB(root);
    // printTree(root);
    // root = insert(root, 20);
    // root = calRB(root);
    // printTree(root);
    // root = insert(root, 9);
    // root = calRB(root);
    // printTree(root);
    // root = insert(root, 17);
    // root = calRB(root);
    // printTree(root);
    // root = insert(root, 18);
    // root = calRB(root);
    // printTree(root);
    // root = insert(root, 32);
    // root = calRB(root);
    // printTree(root);
    // root = insert(root, 27);
    // root = calRB(root);
    // printTree(root);
    // root = insert(root, 42);
    // root = calRB(root);
    // printTree(root);
    // root = insert(root, 80);
    // root = calRB(root);
    // printTree(root);
    // root = insert(root, 4);
    // root = calRB(root);
    // printTree(root);
    // root = insert(root, 2);
    // root = calRB(root);
    // printTree(root);
    return 0;
}

treePointer createTreePointer(treePointer ptrP, treePointer ptr, int num) {
    treePointer newPointer;
    MALLOC(newPointer, sizeof(* newPointer));
    newPointer->parent = (ptrP == ptr) ? NULL : ptrP;
    newPointer->key = num;
    newPointer->color = (ptrP == ptr) ? 'B' : 'R';
    newPointer->leftChild = NULL;
    newPointer->rightChild = NULL;
    return newPointer;
}

treePointer insert(treePointer ptr, int num){
    // printf("insert : %d\n", num);
    return insertRB(ptr, ptr, num);
}

treePointer insertRB(treePointer ptrP, treePointer ptr, int num){
    if(ptr == NULL)
        return createTreePointer(ptrP, ptr, num);
    else if(num < ptr->key)
        ptr->leftChild = insertRB(ptr, ptr->leftChild, num);
    else if(ptr->key < num)
        ptr->rightChild = insertRB(ptr, ptr->rightChild, num);
    return ptr;
}

treePointer calRB(treePointer ptr){
    if(ptr->leftChild != NULL)
        ptr->leftChild = calRB(ptr->leftChild);
    if(ptr->rightChild != NULL)
        ptr->rightChild = calRB(ptr->rightChild);

    if(ptr->leftChild != NULL && ptr->leftChild->color == 'R' 
        && ptr->leftChild->leftChild != NULL && ptr->leftChild->leftChild->color == 'R'){
        // printf("%d L1 L2 ", ptr->key);
        if(ptr->rightChild != NULL && ptr->rightChild->color == 'R'){
            // printf("R3\nchange color : LL_R\n");
            ptr = RBT_CC_R(ptr);
        }else{
            // printf("B3\nrotation : LL_B\n");
            ptr = RBT_LL_B(ptr);
            ptr = RBT_CC_B(ptr);
        }
    }else if(ptr->leftChild != NULL && ptr->leftChild->color == 'R' 
        && ptr->leftChild->rightChild != NULL && ptr->leftChild->rightChild->color == 'R'){
        // printf("%d L1 R2 ", ptr->key);
        if(ptr->rightChild != NULL && ptr->rightChild->color == 'R'){
            // printf("R3\nchange color : LR_R\n");
            ptr = RBT_CC_R(ptr);
        }else{
            // printf("B3\nrotation : LR_B\n");
            ptr = RBT_LR_B(ptr);
            ptr = RBT_CC_B(ptr);
        }
    }else if(ptr->rightChild != NULL && ptr->rightChild->color == 'R'
        && ptr->rightChild->rightChild != NULL && ptr->rightChild->rightChild->color == 'R'){
        // printf("%d R1 R2 ", ptr->key);
        if(ptr->leftChild != NULL && ptr->leftChild->color == 'R'){
            // printf("R3\nchange color : RR_R\n");
            ptr = RBT_CC_R(ptr);
        }else{
            // printf("B3\nrotation : RR_B\n");
            ptr = RBT_RR_B(ptr);
            ptr = RBT_CC_B(ptr);
        }
    }else if(ptr->rightChild != NULL && ptr->rightChild->color == 'R'
        && ptr->rightChild->leftChild != NULL && ptr->rightChild->leftChild->color == 'R'){
        // printf("%d R1 L2 ", ptr->key);
        if(ptr->leftChild != NULL && ptr->leftChild->color == 'R'){
            // printf("R3\nchange color : RL_R\n");
            ptr = RBT_CC_R(ptr);
        }else{
            // printf("B3\nrotation : RL_B\n");
            ptr = RBT_RL_B(ptr);
            ptr = RBT_CC_B(ptr);
        }
    }
    return ptr;
}

treePointer RBT_CC_R(treePointer ptr){
    ptr->color = ptr->parent == NULL ? 'B' : 'R';
    ptr->leftChild->color = 'B';
    ptr->rightChild->color = 'B';
    return ptr;
}

treePointer RBT_CC_B(treePointer ptr){
    ptr->color = 'B';
    if(ptr->leftChild != NULL) ptr->leftChild->color = 'R'; 
    if(ptr->rightChild != NULL) ptr->rightChild->color = 'R';
    return ptr;
}

treePointer RBT_LL_B(treePointer ptr){
    treePointer newPointer;
    MALLOC(newPointer, sizeof(* newPointer));
    newPointer->key = ptr->key;
    newPointer->parent = ptr->leftChild;
    newPointer->rightChild = ptr->rightChild;
    newPointer->leftChild = ptr->leftChild->rightChild;
    ptr->leftChild->parent = ptr->parent == NULL ? NULL : ptr->parent;
    treePointer temp = ptr->leftChild;
    free(ptr);
    ptr = temp;
    ptr->rightChild = newPointer;
    return ptr;
}

treePointer RBT_LR_B(treePointer ptr){
    ptr->leftChild = RBT_RR_B(ptr->leftChild);
    ptr = RBT_LL_B(ptr);
    return ptr;
}

treePointer RBT_RR_B(treePointer ptr){
    treePointer newPointer;
    MALLOC(newPointer, sizeof(* newPointer));
    newPointer->key = ptr->key;
    newPointer->parent = ptr->rightChild;
    newPointer->leftChild = ptr->leftChild;
    newPointer->rightChild = ptr->rightChild->leftChild;
    ptr->rightChild->parent = ptr->parent == NULL ? NULL : ptr->parent;
    treePointer temp = ptr->rightChild;
    free(ptr);
    ptr = temp;
    ptr->leftChild = newPointer;
    return ptr;
}

treePointer RBT_RL_B(treePointer ptr){
    ptr->rightChild = RBT_LL_B(ptr->rightChild);
    ptr = RBT_RR_B(ptr);
    return ptr;
}
