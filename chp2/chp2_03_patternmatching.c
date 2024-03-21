#include <stdio.h>
#include <string.h>
#define MAX_SIZE 100
char string[MAX_SIZE] = {"ABCEABCDABEABCDABCDABDE"};//{"ababbaabaa"};
char pattern[MAX_SIZE] = {"ABCDABD"};//{"aab"};
int nfind(char *, char *);

int main(void){
    // char * t;
    // if(t = strstr(string, pattern))
    //     printf("The string from strstr is : %s\n", t);
    // else
    //     printf("The pattern was not found with strstr\n");
    int ans = nfind(string, pattern);
    if(ans == -1)
        printf("%d\n", ans);
    else
        printf("%d ~ %ld\n", ans + 1, ans + strlen(pattern));
    return 0;
}

int nfind(char * string, char * pattern){
    int i, j, start = 0;
    int lasts = strlen(string) - 1;
    int lastp = strlen(pattern) - 1;
    int endmatch = lastp;
    for(i = 0; endmatch <= lasts; endmatch++, start++){
        if(string[endmatch] == pattern[lastp])
            for(j = 0, i = start; j < lastp && string[i] == pattern[j]; i++, j++);
        if(j == lastp) 
            return start;
    }
    return -1;
    
    // for(i = 0; endmatch <= lasts; endmatch++, start++){
    //     printf("-----------------------------\n");
    //     printf("string[%d] = %c pattern[%d] = %c\n", endmatch, string[endmatch], lastp, pattern[lastp]);
    //     if(string[endmatch] == pattern[lastp]){
    //         printf("compare\n");
    //         for(j = 0, i = start; ; ){
    //             printf("string[%d] = %c pattern[%d] = %c\n", i, string[i], j, pattern[j]);
    //             if(j < lastp && string[i] == pattern[j]){
    //                 i++,j++;
    //             }else{
    //                 break;
    //             }
    //         }
    //     }
    //     if(j == lastp){
    //         printf("find\n");
    //         return start;
    //     }else{
    //         printf("skip\n");
    //     }  
    // }
    // return -1;
}