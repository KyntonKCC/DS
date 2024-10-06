#define MAX_SIZE 150
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MALLOC(p, s)\
    if(!((p) = malloc(s))){\
        fprintf(stderr, "Insufficient memory");\
        exit(EXIT_FAILURE);\
    }
#define REALLOC(p, s)\
    if(!((p) = realloc(p, s))){\
        fprintf(stderr, "Insufficient memory");\
        exit(EXIT_FAILURE);\
    }
typedef struct node_s * treePointer;
typedef struct node_s {
    treePointer leftChild;
    int value;
    treePointer rightChild;
    int shortest;
} node_t;
treePointer buildTree(char *);
treePointer createTreePointer(int);
treePointer insert(treePointer, int);
void reset();
void inorder1(treePointer);     //LVR
void preorder1(treePointer);    //VLR
void postorder1(treePointer);   //LRV
void inorderShortest(treePointer);     //LVR
void preorderShortest(treePointer);    //VLR
void postorderShortest(treePointer);   //LRV
void printTree(treePointer);

int * queue;
int capacityQ = 2;
int front = 2 - 1, rear = -1;
void addq(int);
int deleteq();
void queueFull();
int queueEmpty();
void copy(const int *, const int *, int *);
void printQueue();
int * stack;
int capacityS = 1;
int top = -1;
void push(int);
int pop();
void stackFull();
int stackEmpty();
void printStack();

treePointer buildTree(char * input){
    treePointer root = NULL;
    MALLOC(queue, capacityQ * sizeof(int));
    MALLOC(stack, capacityS * sizeof(int));
    int num_count = 0;
    char * token = strtok(input, "[,]");
    while(token != NULL){
        num_count++;
        for(int i = 0; i <= rear; i++){
            if(queue[i] * 2 <= num_count && queue[rear] < queue[i] * 2){
                addq(queue[i] * 2);
                num_count++;
            }
            if(queue[i] * 2 + 1 <= num_count && queue[rear] < queue[i] * 2 + 1){
                addq(queue[i] * 2 + 1);
                num_count++;
            }
        }
        if(strcmp(token, "null") == 0){
            addq(num_count);
        }else if(strcmp(token, "null") != 0){
            if(root == NULL){
                root = createTreePointer(atoi(token));
            }else{
                int count = num_count;
                while(count != 0 && count != 1){
                    push(count % 2);
                    count /= 2;
                }
                root = insert(root, atoi(token));
            }
        }
        token = strtok(NULL, "[,]");
    }
    return root;
}

treePointer createTreePointer(int num){
    treePointer newTreePointer;
    MALLOC(newTreePointer, sizeof(* newTreePointer));
    newTreePointer->leftChild = NULL;
    newTreePointer->value = num;
    newTreePointer->rightChild = NULL;
    newTreePointer->shortest = 0;
    return newTreePointer;
}

treePointer insert(treePointer ptr, int num){
    if(ptr == NULL)
        return createTreePointer(num);
    int key = pop();
    if(key == 0)
        ptr->leftChild = insert(ptr->leftChild, num);
    else if(key == 1)
        ptr->rightChild = insert(ptr->rightChild, num);
    return ptr;
}

void reset(){
    free(queue);
    free(stack);
    capacityQ = 2;
    front = 1;
    rear = -1;
    capacityS = 1;
    top = -1;
}

void inorder1(treePointer ptr) {
    if (ptr) {
        inorder1(ptr->leftChild);
        printf("%2d ", ptr->value);
        inorder1(ptr->rightChild);
    }
}

void preorder1(treePointer ptr) {
    if (ptr) {
        printf("%2d ", ptr->value);
        preorder1(ptr->leftChild);
        preorder1(ptr->rightChild);
    }
}

void postorder1(treePointer ptr) {
    if (ptr) {
        postorder1(ptr->leftChild);
        postorder1(ptr->rightChild);
        printf("%2d ", ptr->value);
    }
}

void inorderShortest(treePointer ptr) {
    if (ptr) {
        inorderShortest(ptr->leftChild);
        printf("%2d ", ptr->shortest);
        inorderShortest(ptr->rightChild);
    }
}

void preorderShortest(treePointer ptr) {
    if (ptr) {
        printf("%2d ", ptr->shortest);
        preorderShortest(ptr->leftChild);
        preorderShortest(ptr->rightChild);
    }
}

void postorderShortest(treePointer ptr) {
    if (ptr) {
        postorderShortest(ptr->leftChild);
        postorderShortest(ptr->rightChild);
        printf("%2d ", ptr->shortest);
    }
}

void printTree(treePointer ptr){
    printf("------------Recursive Traversals------------");
    printf("\nPreorder:\t");
    preorder1(ptr);
    printf("\nShortest:\t");
    preorderShortest(ptr);
    printf("\nInorder:\t");
    inorder1(ptr);
    printf("\nShortest:\t");
    inorderShortest(ptr);
    printf("\nPostorder:\t");
    postorder1(ptr);
    printf("\nShortest:\t");
    postorderShortest(ptr);
    printf("\n");
}

void addq(int item){
    rear = (rear + 1) % capacityQ;
    if(front == rear)
        queueFull();
    queue[rear] = item;
}

int deleteq(){
    int item;
    if(front == rear){
        return queueEmpty();
    }else{
        front = (front + 1) % capacityQ;
        queue[front] = 0;
        return queue[front];
    }
}

void queueFull(){
    int * newQueue;
    MALLOC(newQueue, 2 * capacityQ * sizeof(int));
    
    int start = (front + 1) % capacityQ;
    if(start < 2){
        copy(queue + start, queue + start + capacityQ - 1, newQueue);
    }else{
        copy(queue + start, queue + capacityQ, newQueue);
        copy(queue, queue + rear + 1, newQueue + capacityQ - start);
    }
    front = 2 * capacityQ - 1;
    rear = capacityQ - 1;
    capacityQ *= 2;
    free(queue);
    queue = newQueue;
}

int queueEmpty(){
    fprintf(stderr, "Queue is empty, cannot delete element\n");
    exit(EXIT_FAILURE);
}

void copy(const int * first, const int * end, int * newQueue){
    int count = end - first;
    for(int i = 0; i < count; i++)
        *(newQueue+i) = *(first+i);
}

void printQueue(){
    for(int i = 0; i < capacityQ; i++)
        printf("%2d ", queue[i]);
    printf("\n");
}

void push(int item){
    if(top >= capacityS - 1)
        stackFull();
    stack[++top] = item;
}

int pop(){
    if(top == -1)
        return stackEmpty();
    else
        return stack[top--];
}

void stackFull(){
    REALLOC(stack, 2 * capacityS * sizeof(int));
    capacityS *= 2;
}

int stackEmpty(){
    fprintf(stderr, "Stack is empty, cannot pop element\n");
    exit(EXIT_FAILURE);
}

void printStack(){
    for(int i = 0; i < capacityS; i++)
        printf("%2d ", stack[i]);
    printf("\n");
}