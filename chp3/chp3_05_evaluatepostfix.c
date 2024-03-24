#include <stdio.h>
#define MAX_STACK_SIZE 100
typedef enum{
    lparen, rparen, plus, minus, times, divide, mod, eos, operand
}precedence;
char expression[MAX_STACK_SIZE];
int stack[MAX_STACK_SIZE];
int eval();
precedence getToken(char *, int *);
void push(int);
int pop();
void stackFull();
int stackEmpty();
int top = -1;

//234*+         //14
//12+7*         //21
//21+62*3/+     //7
//23*6/4+1-     //4
int main(void){
    scanf("%s", expression);
    printf("%d\n", eval());
    return 0;
}

int eval(){
    char symbol;
    int op1, op2;
    int n = 0;
    precedence token = getToken(&symbol, &n);
    while(token != eos){
        if(token == operand){
            push(symbol - '0');
        }else{
            op2 = pop();
            op1 = pop();
            switch(token){
                case plus : push(op1 + op2); break;
                case minus : push(op1 - op2); break;
                case times : push(op1 * op2); break;
                case divide : push(op1 / op2); break;
                case mod : push(op1 % op2); break;
            }
        }
        token = getToken(&symbol, &n);
    }
    return pop();
}

precedence getToken(char * symbol, int * n){
    * symbol = expression[(* n)++];
    switch(* symbol){
        case '(': return lparen;
        case ')': return rparen;
        case '+': return plus;
        case '-': return minus;
        case '/': return divide;
        case '*': return times;
        case '%': return mod;
        case '\0': return eos;
        default : return operand;
    }
}

void push(int item){
    if(top >= MAX_STACK_SIZE - 1)
        stackFull();
    else
        stack[++top] = item;
}

int pop(){
    if(top == -1)
        return stackEmpty();
    else
        return stack[top--];
}

void stackFull(){
    fprintf(stderr, "Stack is full, cannot add element\n");
    // exit(EXIT_FAILURE);
}

int stackEmpty(){
    fprintf(stderr, "Stack is empty, cannot pop element\n");
    // exit(EXIT_FAILURE);
}