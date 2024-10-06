#include <stdio.h>
#include <string.h>
#define MAX_STRING_SIZE 100
#define MAX_PATTERN_SIZE 100
char   string[MAX_STRING_SIZE] = {"ABCABCADABCACBACABCABCACAB"};//{"ABCABCABABCABCDAB"};//{"ABCEABCDABEABCDABCDABDE"};
char pattern[MAX_PATTERN_SIZE] = {"ABCABCACAB"};//{"ABCABCD"};//{"ABCDABD"};
int failure[MAX_PATTERN_SIZE];
void fail(char *);
int pmatch(char *, char *);

int main(void){
    fail(pattern);
    printf("failure :\n");
    for(int i = 0; i < strlen(pattern); i++)
        printf("%3d", i);
    printf("\n");
    for(int i = 0; i < strlen(pattern); i++)
        printf("%3c", pattern[i]);
    printf("\n");
    for(int i = 0; i < strlen(pattern); i++)
        printf("%3d", failure[i]);
    printf("\n");
    int ans = pmatch(string, pattern);
    if(ans == -1)
        printf("%d\n", ans);
    else
        printf("%d ~ %ld\n", ans + 1, ans + strlen(pattern));
    return 0;
}

void fail(char * pattern){
    failure[0] = -1;
    for(int j = 1; j < strlen(pattern); j++){
        int i = failure[j - 1];
        while((pattern[j] != pattern[i + 1]) && i >= 0)
            i = failure[i];
        if(pattern[j] == pattern[i + 1]){
            failure[j] = i + 1;
        }else{
            failure[j] = -1;
        }
    }
}

int pmatch(char * string, char * pattern){
    int i = 0, j = 0;
    int lens = strlen(string);
    int lenp = strlen(pattern);
    while(i < lens && j < lenp){
        // printf("string[%d] = %c pattern[%d] = %c\n", i, string[i], j, pattern[j]);
        if(string[i] == pattern[j])
            i++, j++;
        else if(j == 0)
            i++;
        else
            j = failure[j - 1] + 1;
    }
    return ((j == lenp) ? (i - lenp) : -1);
}