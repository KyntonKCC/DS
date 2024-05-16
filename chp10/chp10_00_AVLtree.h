#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MALLOC(p, s) \
    if(!((p) = malloc(s))) { \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE); \
    }
typedef struct node_s * treePointer;
typedef struct node_s {
    int key;
    int BF;
    int H;
    treePointer leftChild;
    treePointer rightChild;
} node_t;

void printTree(treePointer);
void inorder(treePointer);     //LVR
void preorder(treePointer);    //VLR
void postorder(treePointer);   //LRV
void inorderBF(treePointer);     //LVR
void preorderBF(treePointer);    //VLR
void postorderBF(treePointer);   //LRV
void inorderH(treePointer);     //LVR
void preorderH(treePointer);    //VLR
void postorderH(treePointer);   //LRV

void printTree(treePointer ptr){
    printf("------------Recursive Traversals------------");
    printf("\nPreorder:\t");
    preorder(ptr);
    printf("\nBF:\t\t");
    preorderBF(ptr);
    printf("\nH:\t\t");
    preorderH(ptr);
    printf("\nInorder:\t");
    inorder(ptr);
    printf("\nBF:\t\t");
    inorderBF(ptr);
    printf("\nH:\t\t");
    inorderH(ptr);
    printf("\nPostorder:\t");
    postorder(ptr);
    printf("\nBF:\t\t");
    postorderBF(ptr);
    printf("\nH:\t\t");
    postorderH(ptr);
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

void inorderBF(treePointer ptr) {
    if (ptr) {
        inorderBF(ptr->leftChild);
        printf("%2d ", ptr->BF);
        inorderBF(ptr->rightChild);
    }
}

void preorderBF(treePointer ptr) {
    if (ptr) {
        printf("%2d ", ptr->BF);
        preorderBF(ptr->leftChild);
        preorderBF(ptr->rightChild);
    }
}

void postorderBF(treePointer ptr) {
    if (ptr) {
        postorderBF(ptr->leftChild);
        postorderBF(ptr->rightChild);
        printf("%2d ", ptr->BF);
    }
}

void inorderH(treePointer ptr) {
    if (ptr) {
        inorderH(ptr->leftChild);
        printf("%2d ", ptr->H);
        inorderH(ptr->rightChild);
    }
}

void preorderH(treePointer ptr) {
    if (ptr) {
        printf("%2d ", ptr->H);
        preorderH(ptr->leftChild);
        preorderH(ptr->rightChild);
    }
}

void postorderH(treePointer ptr) {
    if (ptr) {
        postorderH(ptr->leftChild);
        postorderH(ptr->rightChild);
        printf("%2d ", ptr->H);
    }
}