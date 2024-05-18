#define MALLOC(p, s) \
    if(!((p) = malloc(s))) { \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE); \
    }
typedef struct node_s * treePointer;
typedef struct node_s {
    treePointer leftChild;
    int key;
    treePointer rightChild;
} node_t;

void printTree(treePointer);
void inorder(treePointer);     //LVR
void preorder(treePointer);    //VLR
void postorder(treePointer);   //LRV

void printTree(treePointer ptr){
    printf("------------Recursive Traversals------------");
    printf("\nPreorder:\t");
    preorder(ptr);
    printf("\nInorder:\t");
    inorder(ptr);
    printf("\nPostorder:\t");
    postorder(ptr);
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