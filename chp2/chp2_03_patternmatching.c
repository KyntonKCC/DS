#include <stdio.h>
#include <string.h>
#define MAX_SIZE 100
char string[MAX_SIZE] = {"house"};
char pattern[MAX_SIZE] = {"dog"};

int main(void){
    char * t;
    if(t = strstr(string, pattern))
        printf("The string from strstr is : %s\n", t);
    else
        printf("The pattern was not found with strstr\n");
    return 0;
}
