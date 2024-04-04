#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p, s)\
    if(!((p) = malloc(s))){\
        fprintf(stderr, "Insufficient memory");\
        exit(EXIT_FAILURE);\
    }
typedef struct node_s * treePointer;
typedef struct node_s {
    treePointer leftChild;
    int key;
    treePointer rightChild;
} node_t;

treePointer newNode(int);
treePointer insert(treePointer, int);
void splitTree(treePointer, int, treePointer *, treePointer *);
void inorder(treePointer);
void preorder(treePointer);
void postorder(treePointer);

int main(void){
    treePointer root = NULL;
    root = insert(root, 8);
    root = insert(root, 3);
    root = insert(root, 9);
    root = insert(root, 1);
    root = insert(root, 13);
    root = insert(root, 6);
    root = insert(root, 11);
    root = insert(root, 7);
    root = insert(root, 12);
    root = insert(root, 4);
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 14);
    root = insert(root, 2);
    
    printf("Original tree :\n");
    inorder(root);
    printf("\n");
    preorder(root);
    printf("\n");
    postorder(root);
    printf("\n");
/*          
            8
           / \
          /   \
         /     \
        3       9
       / \       \
      /   \       \
     /     \       \
    1       6       13
     \     / \     /  \
      2   4   7   11  14
           \     /  \
            5   10  12
*/
    int key = 6;
    treePointer leftTree = NULL;
    treePointer rightTree = NULL;
    splitTree(root, key, &leftTree, &rightTree);
/*          
        3         8
       / \       / \
      1   4     7   9
       \   \         \
        2   5        13
                    /  \
                   11  14
                  /  \
                 10  12
*/
    printf("Left tree :\n");
    inorder(leftTree);
    printf("\n");
    preorder(leftTree);
    printf("\n");
    postorder(leftTree);
    printf("\n");
    
    printf("Right tree :\n");
    inorder(rightTree);
    printf("\n");
    preorder(rightTree);
    printf("\n");
    postorder(rightTree);
    printf("\n");
    
    return 0;
}

treePointer newNode(int num){
    treePointer temp;
    MALLOC(temp, sizeof(* temp));
    temp->key = num;
    temp->leftChild = NULL;
    temp->rightChild = NULL;
    return temp;
}

treePointer insert(treePointer ptr, int num){
    if(ptr == NULL) 
        return newNode(num);
    if(num < ptr->key)
        ptr->leftChild = insert(ptr->leftChild, num);
    else if(num > ptr->key)
        ptr->rightChild = insert(ptr->rightChild, num);
    return ptr;
}

void splitTree(treePointer ptr, int num, treePointer * leftTree, treePointer * rightTree){
    if(ptr == NULL){
        * leftTree = NULL;
        * rightTree = NULL;
        return;
    }
    if(ptr->key == num){
        * leftTree = ptr->leftChild;
        * rightTree = ptr->rightChild;
        ptr->leftChild = NULL;
        ptr->rightChild = NULL;
        return;
    }else if(num < ptr->key){
        * rightTree = ptr;
        splitTree(ptr->leftChild, num, leftTree, &((* rightTree)->leftChild));
    }else if(num > ptr->key){
        * leftTree = ptr;
        splitTree(ptr->rightChild, num, &((* leftTree)->rightChild), rightTree);
    }
}

void inorder(treePointer ptr){
    if(ptr != NULL){
        inorder(ptr->leftChild);
        printf("%d ", ptr->key);
        inorder(ptr->rightChild);
    }
}
void preorder(treePointer ptr){
    if(ptr != NULL){
        printf("%d ", ptr->key);
        preorder(ptr->leftChild);
        preorder(ptr->rightChild);
    }
}

void postorder(treePointer ptr){
    if(ptr != NULL){
        postorder(ptr->leftChild);
        postorder(ptr->rightChild);
        printf("%d ", ptr->key);
    }
}