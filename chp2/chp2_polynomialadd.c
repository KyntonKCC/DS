#include <stdio.h>
#include <stdlib.h>
#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)
#define MAX_TERM 50
typedef struct{
    float coef;
    int expon;
} polynomial;
polynomial terms[MAX_TERM] = {
    [0] = {.coef = 2,  .expon = 1000},
    [1] = {.coef = 1,  .expon = 0},
    [2] = {.coef = 1,  .expon = 4},
    [3] = {.coef = 10, .expon = 3},
    [4] = {.coef = 3,  .expon = 2},
    [5] = {.coef = 1,  .expon = 0},
};
void padd(int, int, int, int, int *, int *);
void attach(float, int);
int avail = 0;
int startD, finishD;

int main(void){
    avail = 6;
    padd(0, 1, 2, 5, &startD, &finishD);
    for(int i = startD; i <= finishD; i++)
        printf("%d\t%f\n", terms[i].expon, terms[i].coef);
    return 0;
}

void padd(int startA, int finishA, int startB, int finishB, int * startD, int * finishD){
    *startD = avail;
    while(startA <= finishA && startB <= finishB){
        switch(COMPARE(terms[startA].expon, terms[startB].expon)){
            case 1:     // a expon > b expon
                attach(terms[startA].coef, terms[startA].expon);
                startA++;
                break;
            case -1:    // a expon < b expon
                attach(terms[startB].coef, terms[startB].expon);
                startB++;
                break;
            case 0:     // a expon = b expon 
                float coefficient = terms[startA].coef + terms[startB].coef;
                if(coefficient)
                    attach(coefficient, terms[startA].expon);
                startA++;
                startB++;
                break;
        }
    }
    for(; startA <= finishA; startA)
        attach(terms[startA].coef, terms[startA].expon);
    for(; startB <= finishB; startB)
        attach(terms[startB].coef, terms[startB].expon);
    *finishD = avail - 1;
} 

void attach(float coefficient, int exponent){
    if(avail >= MAX_TERM){
        fprintf(stderr, "Too many terms in the polynomial\n");
        exit(EXIT_FAILURE);
    }
    // printf("%d\t%f\n", exponent, coefficient);
    terms[avail].coef = coefficient;
    terms[avail].expon = exponent;
    avail++;
}