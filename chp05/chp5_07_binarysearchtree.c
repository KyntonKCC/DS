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
treePointer minNode(treePointer);
treePointer deleteNode(treePointer, int);
void recsearch(treePointer, int);
void itersearch(treePointer, int);
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
    inorder(root);
    printf("\n");
    preorder(root);
    printf("\n");
    postorder(root);
    printf("\n");
    root = deleteNode(root, 9);
    root = deleteNode(root, 3);
    root = deleteNode(root, 8);
    inorder(root);
    printf("\n");
    preorder(root);
    printf("\n");
    postorder(root);
    printf("\n");
    recsearch(root, 5);
    itersearch(root, 5);
    recsearch(root, 9);
    itersearch(root, 9);
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

treePointer minNode(treePointer ptr){
    treePointer current = ptr;
    while(current->leftChild)
        current = current->leftChild;
    return current;
}

treePointer deleteNode(treePointer ptr, int num){
    if(ptr == NULL)
        return ptr;
    if(num < ptr->key){
        ptr->leftChild = deleteNode(ptr->leftChild, num);
    }else if(num > ptr->key){
        ptr->rightChild = deleteNode(ptr->rightChild, num);
    }else if(num == ptr->key){
        treePointer temp;
        // If the node is with only one child or no child
        if(ptr->leftChild == NULL){
            temp = ptr->rightChild;
            free(ptr);
            return temp;
        }else if(ptr->rightChild == NULL){
            temp = ptr->leftChild;
            free(ptr);
            return temp;
        }else{
            // If the node has two children
            temp = minNode(ptr->rightChild);
            ptr->key = temp->key;
            ptr->rightChild = deleteNode(ptr->rightChild, temp->key);
        }
    }
    return ptr;
}

void recsearch(treePointer ptr, int num){
    if(ptr == NULL){
        printf("Cannot found %d!\n", num);
    }else if(num < ptr->key){
        return recsearch(ptr->leftChild, num);
    }else if(num > ptr->key){
        return recsearch(ptr->rightChild, num);
    }else if(num == ptr->key){
        printf("Found %d!\n", num);
    }
}

void itersearch(treePointer ptr, int num){
    while(ptr){
        if(num < ptr->key){
            ptr = ptr->leftChild;
        }else if(num > ptr->key){
            ptr = ptr->rightChild;
        }else if(num == ptr->key){
            printf("Found %d!\n", num);
            return;
        }
    }
    printf("Cannot found %d!\n", num);
    return;
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
