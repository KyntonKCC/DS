#include <stdio.h>
#define MAX_STACK_SIZE 100
typedef enum{
    lparen, rparen, plus, minus, times, divide, mod, eos, operand
}precedence;
char expression[MAX_STACK_SIZE];
precedence stack[MAX_STACK_SIZE];
char remember[MAX_STACK_SIZE];
int isp[] = {19, 30, 13, 13, 12, 12, 12, 30};
int icp[] = {19, 0, 13, 13, 12, 12, 12, 30};
void prefix();
precedence getToken(char *, int *);
void rememberToken(precedence);
void push(precedence);
precedence pop();
void stackFull();
precedence stackEmpty();
int top = 0, length = 0, count = 0;

//Infix             //Prefix
//A+B*C             //+A*BC
//A*(B+C)*D         //**A+BCD
//(A+B)*C-D/(E+F*G) //-*+ABC/D+E*FG
//D*E/F+A-C         //-+/*DEFAC
//A+B+C*D/E         //++AB/*CDE
int main(void){
    scanf("%s", expression);
    for(int i = 0; expression[i] != '\0'; i++, length++);
    prefix();
    return 0;
}

void prefix(){
    char symbol;
    int n = length - 1;
    stack[0] = eos;
    precedence token = getToken(&symbol, &n);
    while(token != eos){
        if(token == operand){
            remember[count++] = symbol;
        }else if(token == lparen){
            while(stack[top] != rparen)
                rememberToken(pop());
            pop();
        }else{
            while(isp[stack[top]] < icp[token])
                rememberToken(pop());
            push(token);
        }
        token = getToken(&symbol, &n);
    }
    while(top != 0)
        rememberToken(pop());
    for(int i = count; i >= 0; i--)
        printf("%c", remember[i]);
    printf("\n");
}

precedence getToken(char * symbol, int * n){
    * symbol = expression[(* n)--];
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

void rememberToken(precedence item){
    switch(item){
        case plus: remember[count++] = '+'; break;
        case minus: remember[count++] = '-'; break;
        case divide: remember[count++] = '/'; break;
        case times: remember[count++] = '*'; break;
        case mod: remember[count++] = '%'; break;
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