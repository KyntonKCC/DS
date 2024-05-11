#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MALLOC(p, s) \
    if (!((p) = malloc(s))){ \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE); \
    }
typedef struct node_s * treePointer;
typedef struct node_s {
    treePointer leftChild;
    int value;
    treePointer rightChild;
} node_t;
treePointer createTreePointer(int);
//recursive
void inorder1(treePointer);     //LVR
void preorder1(treePointer);    //VLR
void postorder1(treePointer);   //LRV

int main(){
    // char input[1000] = "[2,7,null,50,null,11,null,80,null,13,null]";
    char input[1000] = "[5,9,8,12,null,10,null,20,18,15,null]";
    // int num_count = 0;
    treePointer root = NULL;
    char * token = strtok(input, "[,]");
    while(token != NULL){
        if(strcmp(token, "null") != 0){
            // num_count++;
            treePointer newTreePointer = createTreePointer(atoi(token));
            if(root == NULL){
                root = newTreePointer;
            }else{

            }
        }
        printf("%s ", token);
        token = strtok(NULL, "[,]");
    }
    printf("\n");
    printf("%d\n", root->value);
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

treePointer createTreePointer(int value){
    treePointer newTreePointer;
    MALLOC(newTreePointer, sizeof(* newTreePointer));
    newTreePointer->leftChild = NULL;
    newTreePointer->value = value;
    newTreePointer->rightChild = NULL;
    return newTreePointer;
}

void inorder1(treePointer ptr) {
    if (ptr) {
        inorder1(ptr->leftChild);
        printf("%d ", ptr->value);
        inorder1(ptr->rightChild);
    }
}

void preorder1(treePointer ptr) {
    if (ptr) {
        printf("%d ", ptr->value);
        preorder1(ptr->leftChild);
        preorder1(ptr->rightChild);
    }
}

void postorder1(treePointer ptr) {
    if (ptr) {
        postorder1(ptr->leftChild);
        postorder1(ptr->rightChild);
        printf("%d ", ptr->value);
    }
}