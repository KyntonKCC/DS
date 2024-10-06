#include <stdio.h>
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
#define MAX_SIZE 100
void perm(char *, int, int);

int main(void){
    char list[MAX_SIZE];
    int n;
    scanf("%s %d", list, &n);
    printf("======\n");
    perm(list, 0, n - 1);
    return 0;
}

void perm(char * list, int i, int n){
    int j, tmp;
    if(i == n){
        for(j = 0; j <= n; j++){
            printf("%c", list[j]);
        }
        printf("\n");
    }else{
        for(j = i; j <= n; j++){
            SWAP(list[i], list[j], tmp);
            perm(list, i + 1, n);
            SWAP(list[i], list[j], tmp);
        }
    }
}