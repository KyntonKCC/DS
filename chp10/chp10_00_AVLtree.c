#include <stdio.h>
#include <stdlib.h>
#include "chp10_00_AVLtree.h"
treePointer createTreePointer(int);
treePointer insert(treePointer, int);
treePointer AVL(treePointer);
treePointer AVL_LL(treePointer);
treePointer AVL_LR(treePointer);
treePointer AVL_RR(treePointer);
treePointer AVL_RL(treePointer);
treePointer calBF(treePointer);

int main(){
    treePointer root = NULL;
    root = insert(root, 8);
    root = calBF(root);
    // printTree(root);
    root = insert(root, 9);
    root = calBF(root);
    // printTree(root);
    root = insert(root, 10);
    root = calBF(root);
    // printTree(root);
    root = insert(root, 2);
    root = calBF(root);
    // printTree(root);
    root = insert(root, 1);
    root = calBF(root);
    // printTree(root);
    root = insert(root, 5);
    root = calBF(root);
    // printTree(root);
    root = insert(root, 3);
    root = calBF(root);
    // printTree(root);
    root = insert(root, 6);
    root = calBF(root);
    // printTree(root);
    root = insert(root, 4);
    root = calBF(root);
    // printTree(root);
    root = insert(root, 7);
    root = calBF(root);
    // printTree(root);
    root = insert(root, 11);
    root = calBF(root);
    // printTree(root);
    root = insert(root, 12);
    root = calBF(root);
    printTree(root);
    return 0;
}

treePointer createTreePointer(int num){
    treePointer temp;
    MALLOC(temp, sizeof(* temp));
    temp->key = num;
    temp->BF = 0;
    temp->H = 1;
    temp->leftChild = NULL;
    temp->rightChild = NULL;
    return temp;
}

treePointer insert(treePointer ptr, int num){
    if(ptr == NULL)
        return createTreePointer(num);
    if(num < ptr->key)
        ptr->leftChild = insert(ptr->leftChild, num);
    else if(num > ptr->key)
        ptr->rightChild = insert(ptr->rightChild, num);
    return ptr;
}

treePointer AVL(treePointer ptr){
    if(ptr->BF > 0){
        if(ptr->leftChild->BF > 0)
            ptr = AVL_LL(ptr);
        else if(ptr->leftChild->BF < 0)
            ptr = AVL_LR(ptr);
    }else if(ptr->BF < 0){
        if(ptr->rightChild->BF < 0)
            ptr = AVL_RR(ptr);
        else if(ptr->rightChild->BF > 0)
            ptr = AVL_RL(ptr);
    }
    return ptr;
}

treePointer AVL_LL(treePointer ptr){
    treePointer newPointer;
    MALLOC(newPointer, sizeof(* newPointer));
    newPointer->key = ptr->key;
    newPointer->BF = ptr->BF;
    newPointer->H = ptr->H;
    newPointer->leftChild = ptr->leftChild->rightChild;
    newPointer->rightChild = ptr->rightChild;
    treePointer temp = ptr->leftChild;
    free(ptr);
    ptr = temp;
    ptr->rightChild = newPointer;
    return ptr;
}

treePointer AVL_LR(treePointer ptr){
    ptr->leftChild = AVL_RR(ptr->leftChild);
    ptr = AVL_LL(ptr);
    return ptr;
}

treePointer AVL_RR(treePointer ptr){
    treePointer newPointer;
    MALLOC(newPointer, sizeof(* newPointer));
    newPointer->key = ptr->key;
    newPointer->BF = ptr->BF;
    newPointer->H = ptr->H;
    newPointer->leftChild = ptr->leftChild;
    newPointer->rightChild = ptr->rightChild->leftChild;
    treePointer temp = ptr->rightChild;
    free(ptr);
    ptr = temp;
    ptr->leftChild = newPointer;
    return ptr;
}

treePointer AVL_RL(treePointer ptr){
    ptr->rightChild = AVL_LL(ptr->rightChild);
    ptr = AVL_RR(ptr);
    return ptr;
}

treePointer calBF(treePointer ptr){
    if(ptr->leftChild != NULL)
        ptr->leftChild = calBF(ptr->leftChild);
    if(ptr->rightChild != NULL)
        ptr->rightChild = calBF(ptr->rightChild);
    int leftH = ptr->leftChild == NULL ? 0 : ptr->leftChild->H;
    int rightH = ptr->rightChild == NULL ? 0 : ptr->rightChild->H;
    ptr->BF = leftH - rightH;
    ptr->H = MAX(leftH, rightH) + 1;
    if(ptr->BF < -1 || 1 < ptr->BF){
        ptr = AVL(ptr);
        ptr = calBF(ptr);
    }
    return ptr;
}
