#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
#define MALLOC(p, s)\
    if(!((p) = malloc(s))){\
        fprintf(stderr, "Insufficient memory");\
        exit(EXIT_FAILURE);\
    }
typedef struct node_s * treePointer;
typedef struct node_s {
    treePointer leftChild;
    char key;
    treePointer rightChild;
} node_t;
char Pre[MAX_SIZE], In[MAX_SIZE], Post[MAX_SIZE];
int n;
treePointer newNode(char);
int findInPosition(int, int, char);
treePointer buildPre(int, int, int, int);
treePointer buildPost(int, int, int, int);
int findPrePosition(int, int, char);
int findPostPosition(int, int, char);
treePointer buildIn(int, int, int, int);
void inorder(treePointer);
void preorder(treePointer);
void postorder(treePointer);
//Catalan
//C(0) = C(1) = 1
//C(n+1) = C(0)*C(n) + C(1)*C(n−1) + ... + C(n−1)*C(1) + C(n)*C(0), n >= 2

/*        
               A
              / \
             /   \
            /     \
           /       \
          /         \
         B           C
        / \         / \
       /   \       /   \
      D     E     F     G
     / \   / \   / \   / \
    H   I J   K L   M N   O

Number :    15
PreOrder :  ABDHIEJKCFLMGNO
            ABDHIEJKCFLMGNO
InOrder :   HDIBJEKALFMCNGO
            HDIBJEKALFMCNGO --> only in Complete Binary Tree
PostOrder : HIDJKEBLMFNOGCA
            HIDJKEBLMFNOGCA

            A
           / \
          B   I
         / \   \
        C   H   J
       / \
      D   G
     / \
    E   F

Number :    10
PreOrder :  ABCDEFGHIJ
            ABCDEFGHIJ
InOrder :   EDFCGBHAIJ
            EDFCGBHAJIJ --> only in Complete Binary Tree, or false
PostOrder : EFDGCHBJIA
            EFDGCHBJIA

potential tree :      A   A
PreOrder :  AB       /     \
PostOrder : BA      B       B
--> Not Unique
*/

int main(void){

    printf("Number of elements : ");
    scanf("%d", &n);
    int dp[n+1];
    for(int i = 0; i < n + 1; i++)
        dp[i] = 0;
    dp[0] = dp[1] = 1;
    for(int i = 2; i <= n; i++)
        for(int j = 0; j < i; j++)
            dp[i] += dp[j] * dp[i - j - 1];
    printf("Number of Distinct Binary Tree : %d\n", dp[n]);
    //Catalan formula : C(2n,n)/(n+1)
    // long res = 1 ;
    // for (int i = n + 1 ; i <= 2 * n; i++) 
    //     res = res * i / (i - n);
    // printf("Number of Distinct Binary Tree : %ld\n", res / (n + 1));

    printf("Select two to order , the other input ('?')\n");
    printf("PreOrder :  ");
    scanf("%s", Pre);
    printf("Inorder :   ");
    scanf("%s", In);
    printf("PostOrder : ");
    scanf("%s", Post);
    if(Post[0] == '?'){         //Pre & In
        treePointer ptr = buildPre(0, n-1, 0, n-1);
        printf("PostOrder : ");
        postorder(ptr);
        printf("\n");
    }else if(Pre[0] == '?'){    //In & Post
        treePointer ptr = buildPost(0, n-1, 0, n-1);
        printf("PreOrder :  ");
        preorder(ptr);
        printf("\n");
    }else if(In[0] == '?'){    //Pre & Post --> only in Complete Binary Tree
        treePointer ptr = buildIn(0, n-1, 0, n-1);
        printf("Inorder :   ");
        inorder(ptr);
        printf("\n");
    }
    return 0;
}

treePointer newNode(char ch){
    treePointer temp;
    MALLOC(temp, sizeof(* temp));
    temp->key = ch;
    temp->leftChild = NULL;
    temp->rightChild = NULL;
    return temp;
}

int findInPosition(int S, int E, char ch){
    for(int i = S; i <= E; i++)
        if(In[i] == ch)
            return i;
    return -1;
}

treePointer buildPre(int preS, int preE, int inS, int inE){
    treePointer ptr = newNode(Pre[preS]);
    int position = findInPosition(inS, inE, Pre[preS]);
    if(position != inS)
        ptr->leftChild = buildPre(preS + 1, preS + (position - inS), inS, position - 1);
    if(position != inE)
        ptr->rightChild = buildPre(preE - (inE - position) + 1, preE, position + 1, inE);
    return ptr;
}

treePointer buildPost(int postS, int postE, int inS, int inE){
    treePointer ptr = newNode(Post[postE]);
    int position = findInPosition(inS, inE, Post[postE]);
    if(position != inS)
        ptr->leftChild = buildPost(postS, postS + (position - inS) - 1, inS, position - 1);
    if(position != inE)
        ptr->rightChild = buildPost(postE - (inE - position), postE - 1, position + 1, inE);
    return ptr;
}

int findPrePosition(int S, int E, char ch){
    for(int i = S; i <= E; i++)
        if(Pre[i] == ch)
            return i;
    return -1;
}

int findPostPosition(int S, int E, char ch){
    for(int i = S; i <= E; i++)
        if(Post[i] == ch)
            return i;
    return -1;
}

treePointer buildIn(int preS, int preE, int postS, int postE){
    treePointer ptr = newNode(Pre[preS]);
    int p1 = findPrePosition(preS + 1, preE, Post[postE - 1]);
    int p2 = findPostPosition(postS, postE - 1, Pre[preS + 1]);
    if(preE != preS)
        ptr->leftChild = buildIn(preS + 1, preS + 1 + (p2 - postS), postS, p2);
    if(postS != postE)
        ptr->rightChild = buildIn(p1, preE, postE - 1 - (preE - p1), postE - 1);
    return ptr;
}

void inorder(treePointer ptr){
    if(ptr == NULL) return;
    inorder(ptr->leftChild);
    printf("%c", ptr->key);
    inorder(ptr->rightChild);
}
void preorder(treePointer ptr){
    if(ptr == NULL) return;
    printf("%c", ptr->key);
    preorder(ptr->leftChild);
    preorder(ptr->rightChild);
}

void postorder(treePointer ptr){
    if(ptr == NULL) return;
    postorder(ptr->leftChild);
    postorder(ptr->rightChild);
    printf("%c", ptr->key);
}