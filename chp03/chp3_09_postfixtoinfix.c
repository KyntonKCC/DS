#include <stdio.h>
#define MAX_STACK_SIZE 100
typedef enum{
    lparen, rparen, plus, minus, times, divide, mod, eos, operand
}precedence;
char expression[MAX_STACK_SIZE];
char remember[MAX_STACK_SIZE];
int size[MAX_STACK_SIZE];
void infix();
precedence getToken(char *, int *);
void rememberToken(precedence);
void push(char);
char pop();
void stackFull();
char stackEmpty();
int remtop = -1, sizetop = -1;

//Postfix       //Infix 
//ABC*+         //(A+(B*C))
//ABC+*D*       //((A*(B+C))*D)
//AB+C*DEFG*+/- //(((A+B)*C)-(D/(E+(F*G))))
//AB+C/D*       //(((A+B)/C)*D)
//AB-CD*E*F/+G- //(((A-B)+(((C*D)*E)/F))-G)
int main(void){
    scanf("%s", expression);
    infix();
    return 0;
}

void infix(){
    char symbol;
    int n = 0;
    precedence token = getToken(&symbol, &n);
    while(token != eos){
        if(token == operand){
            push(symbol);
            size[++sizetop] = 1;
            // printf("%c %d, remtop = %d, sizetop = %d\n", remember[remtop], size[sizetop], remtop, sizetop);
        }else{
            char op1[MAX_STACK_SIZE], op2[MAX_STACK_SIZE];
            // printf("size = %d op2 : ", size[sizetop]);
            for(int i = 0; i < size[sizetop]; i++){
                op2[i] = pop();
                // printf("%c ", op2[i]);
            }
            // printf("\nsize = %d op1 : ", size[sizetop - 1]);
            for(int i = 0; i < size[sizetop - 1]; i++){
                op1[i] = pop();
                // printf("%c ", op1[i]);
            }
            // printf("\n");
            push('(');
            for(int i = size[sizetop - 1] - 1; i >= 0; i--)
                push(op1[i]);
            rememberToken(token);
            for(int i = size[sizetop] - 1; i >= 0; i--)
                push(op2[i]);
            push(')');
            size[sizetop - 1] = size[sizetop] + size[sizetop - 1] + 3;
            size[sizetop] = 0;
            sizetop--;
        }
        token = getToken(&symbol, &n);
    }
    for(int i = 0; i <= remtop; i++)
        printf("%c", remember[i]);
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

void rememberToken(precedence item){
    switch(item){
        case plus: push('+'); break;
        case minus: push('-'); break;
        case divide: push('/'); break;
        case times: push('*'); break;
        case mod: push('%'); break;
    }
}

void push(char item){
    if(remtop >= MAX_STACK_SIZE - 1)
        stackFull();
    else
        remember[++remtop] = item;
}

char pop(){
    if(remtop == -1)
        return stackEmpty();
    else
        return remember[remtop--];
}

void stackFull(){
    fprintf(stderr, "Stack is full, cannot add element\n");
    // exit(EXIT_FAILURE);
}

char stackEmpty(){
    fprintf(stderr, "Stack is empty, cannot pop element\n");
    // exit(EXIT_FAILURE);
}