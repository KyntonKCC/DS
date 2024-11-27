#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// define tree node structure
typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// create tree node
TreeNode* createNode(int key) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->val = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// insert node
TreeNode* insert(TreeNode* node, int key) {
    // complete the content of this function
    if(node == NULL)
        return createNode(key);
    if(key < node->val)
        node->left = insert(node->left, key);
    else if(key > node->val)
        node->right = insert(node->right, key);
    return node;
}

TreeNode* maxValueNode(TreeNode* node) {
    TreeNode* current = node;
    while (current && current->right != NULL) {
        current = current->right;
    }
    return current;
}

// delete node
TreeNode* deleteNode(TreeNode* root, int key) {
    // complete the content of this function
    if(root == NULL)
        return root;
    if(key < root->val){
        root->left = deleteNode(root->left, key);
    }else if (key > root->val){
        root->right = deleteNode(root->right, key);
    }else if(key == root->val){
        TreeNode* temp;
        if(root->left == NULL){
            temp = root->right;
            free(root);
            return temp;
        }else if(root->right == NULL){
            temp = root->left;
            free(root);
            return temp;
        }else{
            temp = maxValueNode(root->left);
            root->val = temp->val;
            root->left = deleteNode(root->left, temp->val);
        }
    }
    return root;
}

// level order
void levelOrder(TreeNode* root) {
    if (root == NULL) return;

    TreeNode** queue = (TreeNode**)malloc(100 * sizeof(TreeNode*)); // 假設最大節點數
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        TreeNode* current = queue[front++];
        printf("%d ", current->val);
        if (current->left) queue[rear++] = current->left;
        if (current->right) queue[rear++] = current->right;
    }

    free(queue);
}

// main function
int main() {
    TreeNode* root = NULL;
    char operation[10];
    int value;

    while (1) {
        scanf("%s", operation);
        if (strcmp(operation, "exit") == 0) break;
        scanf("%d", &value);

        if (strcmp(operation, "insert") == 0) {
            root = insert(root, value);
        } else if (strcmp(operation, "delete") == 0) {
            root = deleteNode(root, value);
        } else {
            printf("Invalid operation\n");
        }
    }

    levelOrder(root);
    printf("\n");

    return 0;
}
