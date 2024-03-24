#include <stdio.h>
#define MAX_STACK_SIZE 100
typedef enum{
    lparen, rparen, plus, minus, times, divide, mod, eos, operand
}precedence;
char expression[MAX_STACK_SIZE];
precedence stack[MAX_STACK_SIZE];
int isp[] = {0, 19, 12, 12, 13, 13, 13, 0};
int icp[] = {20, 19, 12, 12, 13, 13, 13, 0};
void postfix();
precedence getToken(char *, int *);
void printToken(precedence);
void push(precedence);
precedence pop();
void stackFull();
precedence stackEmpty();
int top = 0;

//Infix             //Postfix
//A+B*C             //ABC*+
//A*(B+C)*D         //ABC+*D*
//(A+B)*C-D/(E+F*G) //AB+C*DEFG*+/-
//(A+B)/C*D         //AB+C/D*
//A-B+C*D*E/F-G     //AB-CD*E*F/+G-
int main(void){
    scanf("%s", expression);
    postfix();
    return 0;
}

void postfix(){
    char symbol;
    int n = 0;
    stack[0] = eos;
    precedence token = getToken(&symbol, &n);
    while(token != eos){
        if(token == operand){
            printf("%c", symbol);
        }else if(token == rparen){
            while(stack[top] != lparen)
                printToken(pop());
            pop();
        }else{
            while(isp[stack[top]] >= icp[token])
                printToken(pop());
            push(token);
        }
        token = getToken(&symbol, &n);
    }
    for(int i = top; i > 0; i--)
        printToken(pop());
    printf("\n");
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

void printToken(precedence item){
    switch(item){
        case plus: printf("+"); break;
        case minus: printf("-"); break;
        case divide: printf("/"); break;
        case times: printf("*"); break;
        case mod: printf("%%"); break;
    }
}

void push(precedence item){
    if(top >= MAX_STACK_SIZE - 1)
        stackFull();
    else
        stack[++top] = item;
}

precedence pop(){
    if(top == -1)
        return stackEmpty();
    else
        return stack[top--];
}

void stackFull(){
    fprintf(stderr, "Stack is full, cannot add element\n");
    // exit(EXIT_FAILURE);
}

precedence stackEmpty(){
    fprintf(stderr, "Stack is empty, cannot pop element\n");
    // exit(EXIT_FAILURE);
}