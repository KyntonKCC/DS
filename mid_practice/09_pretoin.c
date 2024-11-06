#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 50
typedef enum{
    lparen, rparen, plus, minus, times, divide, mod, eos, operand
}precedence;
char expression[MAX_STACK_SIZE];
char remember[MAX_STACK_SIZE];
int size[MAX_STACK_SIZE];
int remtop = -1, sizetop = -1, length = 0;
void pretoin();
precedence getToken(char *, int *);
void rememberToken(precedence);
void push(char);
char pop();
void stackFull();
char stackEmpty();

int main(void){
    scanf("%s", expression);
    for(int i = 0; expression[i] != '\0'; i++, length++);
    pretoin();
    return 0;
}

void pretoin(){
    char symbol;
    int n = length - 1;
    precedence token = getToken(&symbol, &n);
    while(token != eos){
        if(token == operand){
            push(symbol);
            size[++sizetop] = 1;
        }else{
            char op1[size[sizetop - 1]], op2[size[sizetop]];
            for(int i = 0; i < size[sizetop]; i++)
                op2[i] = pop();
            for(int i = 0; i < size[sizetop - 1]; i++)
                op1[i] = pop();
            push(')');
            for(int i = size[sizetop - 1] - 1; i >= 0; i--)
                push(op1[i]);
            rememberToken(token);
            for(int i = size[sizetop] - 1; i >= 0; i--)
                push(op2[i]);
            push('(');
            size[sizetop - 1] = size[sizetop] + size[sizetop - 1] + 3;
            size[sizetop] = 0;
            sizetop--;
        }
        token = getToken(&symbol, &n);
    }
    for(int i = remtop; i >= 0; i--)
        printf("%c", remember[i]);
    printf("\n");
}

precedence getToken(char *symbol, int *n){
    *symbol = expression[(*n)--];
    switch(*symbol){
        case '(': return lparen; 
        case ')': return rparen;
        case '+': return plus;
        case '-': return minus;
        case '*': return times;
        case '/': return divide;
        case '%': return mod;
        case '\0': return eos;
        default : return operand;
    }
}

void rememberToken(precedence item){
    switch(item){
        case plus: push('+'); break;
        case minus: push('-'); break;
        case times: push('*'); break;
        case divide: push('/'); break;
        case mod: push('%'); break;
    }
}

void push(char item){
    if(remtop >= MAX_STACK_SIZE - 1){
        stackFull();
    }else{
        remember[++remtop] = item;
    }
}

char pop(){
    if(remtop == -1){
        return stackEmpty();
    }else{
        return remember[remtop--];
    }
}

void stackFull(){
    printf("FULL\n");
    exit(EXIT_SUCCESS);
}

char stackEmpty(){
    printf("EMPTY\n");
    exit(EXIT_SUCCESS);
}