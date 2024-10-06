#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>
#define MALLOC(p, s)\
    if(!((p) = malloc(s))){\
        fprintf(stderr, "Insufficient memory");\
        exit(EXIT_FAILURE);\
    }
#define MAX_SIZE 24
#define FALSE 0
#define TRUE 1
typedef struct node * nodePointer;
struct node{
    int data;
    nodePointer link;
};

int main(void){
    int out[MAX_SIZE];
    nodePointer seq[MAX_SIZE];
    nodePointer x, y, top;
    int i, j, n;

    printf("Enter the size (<= %d) ", MAX_SIZE);
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        out[i] = TRUE;
        seq[i] = NULL;
    }

    do{
        printf("Enter a pair of numbers (-1 -1 to quit) : ");
        scanf("%d %d", &i, &j);
        MALLOC(x, sizeof(nodePointer));
        x->data = j;
        x->link = seq[i];
        seq[i] = x;
        MALLOC(x, sizeof(nodePointer));
        x->data = i;
        x->link = seq[j];
        seq[j] = x;
    }while(i >= 0);

    for(int i = 0; i < n; i++){     //?????
        if(out[i]){
            printf("\nNew class : %5d", i);
            out[i] = FALSE;
            x = seq[i];
            top = NULL;
            for(;;){
                while(x){
                    j = x->data;
                    if(out[j]){
                        printf("%5d", j);
                        out[j] = FALSE;
                        y = x->link;
                        x->link = top;
                        top = x;
                        x = y;
                    }else{
                        x = x->link;
                    }
                }
                if(!top) break;
                x = seq[top->data];
                top = top->link;
            }
        }
    }
    printf("\n");
    return 0;
}

