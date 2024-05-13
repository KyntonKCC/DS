#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 150
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
} node_t;
treePointer createTreePointer(int);
treePointer insert(treePointer, int);
void inorder1(treePointer);     //LVR
void preorder1(treePointer);    //VLR
void postorder1(treePointer);   //LRV

/*
int queue[MAX_SIZE];
void addq(int);
int deleteq();
void queueFull();
int queueEmpty();
void printQueue();
int front = -1, rear = -1;
int stack[MAX_SIZE];
void push(int);
int pop();
void stackFull();
int stackEmpty();
int top = -1;
*/

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

/*
          2                  __5__
         / \                /     \
        7   50             9       8
       /    /             /       /
      11  80             12      10
     /                  /  \    /
    13                 20  18  15

         1                  _3_
        / \                /   \
      10   8              4     7
      /   /              / \   / 
    12   11             6  20 10  
        /              / \   /
       16             25 21 15
                     /
                    27
*/

int main(){
    treePointer root = NULL;
    MALLOC(queue, capacityQ * sizeof(int));
    MALLOC(stack, capacityS * sizeof(int));
    // char input[MAX_SIZE] = "[2,7,50,11,null,80,null,13]";
    // char input[MAX_SIZE] = "[5,9,8,12,null,10,null,20,18,15]";
    // char input[MAX_SIZE] = "[1,10,8,12,null,11,null,null,null,16]";
    char input[MAX_SIZE] = "[3,4,7,6,20,10,null,25,21,null,null,15,null,27]";
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
        printf("%s -> %d\n", token, num_count);
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
        printf("\n");
        token = strtok(NULL, "[,]");
    }
    printf("\nqueue : ");
    printQueue();
    printf("\n------------Recursive Traversals------------");
    printf("\nPreorder:\t");
    preorder1(root);
    printf("\nInorder:\t");
    inorder1(root);
    printf("\nPostorder:\t");
    postorder1(root);
    printf("\n");
    return 0;
}

treePointer createTreePointer(int num){
    treePointer newTreePointer;
    MALLOC(newTreePointer, sizeof(* newTreePointer));
    newTreePointer->leftChild = NULL;
    newTreePointer->value = num;
    newTreePointer->rightChild = NULL;
    return newTreePointer;
}

treePointer insert(treePointer ptr, int num){
    if(ptr == NULL)
        return createTreePointer(num);
    int key = pop();
    if(key == 0){
        printf("->left");
        ptr->leftChild = insert(ptr->leftChild, num);
    }else if(key == 1){
        printf("->right");
        ptr->rightChild = insert(ptr->rightChild, num);
    }
    return ptr;
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

/*
void addq(int item){
    if(rear == MAX_SIZE - 1)
        queueFull();
    else
        queue[++rear] = item;
}

int deleteq(){
    if(front == rear)
        return queueEmpty();
    else
        return queue[++front];
}

void queueFull(){
    fprintf(stderr, "Queue is full, cannot add element\n");
    // exit(EXIT_FAILURE);
}

int queueEmpty(){
    fprintf(stderr, "Queue is empty, cannot delete element\n");
    // exit(EXIT_FAILURE);
}

void printQueue(){
    for(int i = 0; i <= rear; i++)
        printf("%d ", queue[i]);
    printf("\n");
}

void push(int item){
    if(top >= MAX_SIZE - 1)
        stackFull();
    else
        stack[++top] = item;
}

int pop(){
    if(top == -1)
        return stackEmpty();
    else
        return stack[top--];
}

void stackFull(){
    fprintf(stderr, "Stack is full, cannot add element\n");
    // exit(EXIT_FAILURE);
}

int stackEmpty(){
    fprintf(stderr, "Stack is empty, cannot pop element\n");
    // exit(EXIT_FAILURE);
}
*/

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
    printf("Queue is full, cannot add element, update capacity = %d -> %d\n", capacityQ, capacityQ * 2);
    int * newQueue;
    MALLOC(newQueue, 2 * capacityQ * sizeof(int));
    
    int start = (front + 1) % capacityQ;
    if(start < 2){
        // X X X O
        // O X X X
        copy(queue + start, queue + start + capacityQ - 1, newQueue);
    }else{
        // X O X X
        // X X O X
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
    // exit(EXIT_FAILURE);
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
    if(top == -1){
        return stackEmpty();
    }else{
        // stack[top] = 0;
        return stack[top--];
    }
}

void stackFull(){
    printf("Stack is full, cannot add element, update capacity = %d -> %d\n", capacityS, capacityS * 2);
    REALLOC(stack, 2 * capacityS * sizeof(int));
    capacityS *= 2;
}

int stackEmpty(){
    fprintf(stderr, "Stack is empty, cannot pop element\n");
    // exit(EXIT_FAILURE);
}

void printStack(){
    for(int i = 0; i < capacityS; i++)
        printf("%2d ", stack[i]);
    printf("\n");
}