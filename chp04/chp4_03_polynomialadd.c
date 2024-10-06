#include <stdio.h>
#include <stdlib.h>
#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)
#define MALLOC(p, s)\
    if(!((p) = malloc(s))){\
        fprintf(stderr, "Insufficient memory");\
        exit(EXIT_FAILURE);\
    }
typedef struct polyNode * polyPointer;
struct polyNode{
    int coef;
    int expon;
    polyPointer link;
};
polyPointer a, b, c;
polyPointer padd(polyPointer, polyPointer);
void attach(float, int, polyPointer *);
void printPoly(polyPointer);

int main(void){
    {MALLOC(a, sizeof(polyPointer));
    a->coef = 3;
    a->expon = 14;
    MALLOC(a->link, sizeof(polyPointer));
    a->link->coef = 2;
    a->link->expon = 8;
    MALLOC(a->link->link, sizeof(polyPointer));
    a->link->link->coef = 1;
    a->link->link->expon = 0;
    a->link->link->link = NULL;
    MALLOC(b, sizeof(polyPointer));
    b->coef = 8;
    b->expon = 14;
    MALLOC(b->link, sizeof(polyPointer));
    b->link->coef = -3;
    b->link->expon = 10;
    MALLOC(b->link->link, sizeof(polyPointer));
    b->link->link->coef = 10;
    b->link->link->expon = 6;
    b->link->link->link = NULL;};

    printf("----A----\n");
    printPoly(a);
    printf("----B----\n");
    printPoly(b);
    printf("----C----\n");
    c = padd(a, b);
    printPoly(c);
    return 0;
}

void printPoly(polyPointer ptr){
    while(ptr != NULL){
        printf("%4d %3d\n", ptr->coef, ptr->expon);
        ptr = ptr->link;
    }
}

polyPointer padd(polyPointer a, polyPointer b){
    polyPointer rear;
    MALLOC(rear, sizeof(polyPointer));
    c = rear;
    while(a && b){
        switch(COMPARE(a->expon, b->expon)){
            case 1:
                attach(a->coef, a->expon, &rear);
                a = a->link;
                break;
            case -1:
                attach(b->coef, b->expon, &rear);
                b = b->link;
                break;
            case 0:
                int sum = a->coef + b->coef;
                if(sum)
                    attach(sum, a->expon, &rear);
                a = a->link;
                b = b->link;
                break;
        }
    }
    for(; a; a = a->link)
        attach(a->coef, a->expon, &rear);
    for(; b; b = b->link)
        attach(b->coef, b->expon, &rear);
    rear->link = NULL;
    return c->link;
}

void attach(float coefficient, int exponent, polyPointer * ptr){
    polyPointer temp;
    MALLOC(temp, sizeof(polyPointer));
    temp->coef = coefficient;
    temp->expon = exponent;
    temp->link = NULL;
    (* ptr)->link = temp;
    (* ptr) = (* ptr)->link;
}
