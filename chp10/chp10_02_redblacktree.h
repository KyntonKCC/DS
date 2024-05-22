#define MALLOC(p, s) \
    if(!((p) = malloc(s))) { \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE); \
    }
typedef struct node_s * treePointer;
typedef struct node_s {
    treePointer parent;
    int key;
    char color;
    treePointer leftChild;
    treePointer rightChild;
} node_t;

void printTree(treePointer);
void inorder(treePointer);     //LVR
void preorder(treePointer);    //VLR
void postorder(treePointer);   //LRV
void inorderC(treePointer);     //LVR
void preorderC(treePointer);    //VLR
void postorderC(treePointer);   //LRV

void printTree(treePointer ptr){
    printf("------------Recursive Traversals------------");
    printf("\nPreorder:\t");
    preorder(ptr);
    printf("\nColor:\t\t");
    preorderC(ptr);
    printf("\nInorder:\t");
    inorder(ptr);
    printf("\nColor:\t\t");
    inorderC(ptr);
    printf("\nPostorder:\t");
    postorder(ptr);
    printf("\nColor:\t\t");
    postorderC(ptr);
    printf("\n");
}

void inorder(treePointer ptr) {
    if (ptr) {
        inorder(ptr->leftChild);
        printf("%2d ", ptr->key);
        inorder(ptr->rightChild);
    }
}

void preorder(treePointer ptr) {
    if (ptr) {
        printf("%2d ", ptr->key);
        preorder(ptr->leftChild);
        preorder(ptr->rightChild);
    }
}

void postorder(treePointer ptr) {
    if (ptr) {
        postorder(ptr->leftChild);
        postorder(ptr->rightChild);
        printf("%2d ", ptr->key);
    }
}

void inorderC(treePointer ptr) {
    if (ptr) {
        inorderC(ptr->leftChild);
        printf(" %c ", ptr->color);
        inorderC(ptr->rightChild);
    }
}

void preorderC(treePointer ptr) {
    if (ptr) {
        printf(" %c ", ptr->color);
        preorderC(ptr->leftChild);
        preorderC(ptr->rightChild);
    }
}

void postorderC(treePointer ptr) {
    if (ptr) {
        postorderC(ptr->leftChild);
        postorderC(ptr->rightChild);
        printf(" %c ", ptr->color);
    }
}