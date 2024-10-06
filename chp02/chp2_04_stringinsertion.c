#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 100
char s[MAX_SIZE] = {"amobile"};
char t[MAX_SIZE] = {"uto"};
void strnins(char *, char *, int);

int main(void){
    strnins(s, t, 1);
    for(int i = 0; i < strlen(s); i++)
        printf("%c ", s[i]);
    printf("\n");
    return 0;
}

void strnins(char * s, char * t, int i){
    char string[MAX_SIZE], * temp = string;
    if(i < 0 && i > strlen(s)){
        fprintf(stderr, "Position is out of bounds\n");
        exit(EXIT_FAILURE);
    }
    if(!strlen(s)){
        //s -->\0
        strcpy(s, t);
        //s -->u t o \0
    }else if(strlen(t)){
        //temp -->\0
        strncpy(temp, s, i);
        //temp -->a \0
        strcat(temp, t);
        //temp -->a u t o \0
        strcat(temp, (s + i));
        //temp -->a u t o m o b i l e \0
        strcpy(s, temp);
        //s -->a u t o m o b i l e \0
    }
}