#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 50
typedef enum{
    lparen, rparen, plus, minus, times, divide, mod, eos, operand
}precedence;
char expression[MAX_STACK_SIZE];
precedence stack[MAX_STACK_SIZE];
char remember[MAX_STACK_SIZE];
int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0};
int icp[] = {20, 19, 12, 12, 13, 13, 13, 0};
int top = 0, count = 0;
void intopost();
precedence getToken(char *, int *);
void rememberToken(precedence);
void push(precedence);
precedence pop();
void stackFull();
precedence stackEmpty();

int main(void){
    scanf("%s", expression);
    intopost();
    return 0;
}

void intopost(){
    char symbol;
    int n = 0;
    stack[0] = eos;
    precedence token = getToken(&symbol, &n);
    while(token != eos){
        if(token == operand){
            remember[count++] = symbol;
        }else if(token == rparen){
            while(stack[top] != lparen)
                rememberToken(pop());
            pop();
        }else{
            while(isp[stack[top]] >= icp[token])
                rememberToken(pop());
            push(token);
        }
        token = getToken(&symbol, &n);
    }
    while(top != 0)
        rememberToken(pop());
    for(int i = 0; i < count; i++)
        printf("%c", remember[i]);
    printf("\n");
}

precedence getToken(char *symbol, int *n){
    *symbol = expression[(*n)++];
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
        case plus : remember[count++] = '+'; break;
        case minus : remember[count++] = '-'; break;
        case times : remember[count++] = '*'; break;
        case divide : remember[count++] = '/'; break;
        case mod : remember[count++] = '%'; break;
    }
}

void push(precedence num){
    if(top >= MAX_STACK_SIZE - 1){
        stackFull();
    }else{
        stack[++top] = num;
    }
}

precedence pop(){
    if(top == -1){
        return stackEmpty();
    }else{
        return stack[top--];
    }
}

void stackFull(){
    printf("Full\n");
    exit(EXIT_SUCCESS);
}

precedence stackEmpty(){
    printf("Empty\n");
    exit(EXIT_SUCCESS);
}