#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "rpn.h"

#define MAX 100

// Creating a stack
struct stack
{
    char items[MAX];
    int top;
};

typedef struct stack st;

void create_empty_stack(st *s)
{
    s->top = -1;
}

// Check if the stack is full
int is_full(st *s)
{
    if (s->top == MAX - 1)
        return 1;
    else
        return 0;
}

// Check if the stack is empty
int is_empty(st *s)
{
    if (s->top == -1)
        return 1;
    else
        return 0;
}

// Add elements into stack
void push(st *s, int new_item)
{
    if (is_full(s))
    {
        printf("STACK FULL");
    }
    else
    {
        s->top++;
        s->items[s->top] = new_item;
    }
}

// Remove element from stack
char pop(st *s)
{
    char ret;

    if (is_empty(s))
    {
        printf("\n STACK EMPTY \n");
    }
    else
    {
        ret = s->items[s->top];
        s->top--;
    }
    return ret;
}

char peek(st *s)
{
    char ret;

    if (is_empty(s))
    {
        printf("\n STACK EMPTY \n");
    }
    else
    {
        ret = s->items[s->top];
    }
    return ret;
}


int precedence(char ch){
    if (ch == '+' || ch == '-')
            return 1;
        else if (ch == '*' || ch == '/')
            return 2;
        else
            return -1;
}

//Shunting-yard algorithm
char* convert_rpn(char *str){

    char *output = malloc(sizeof(str)/sizeof(char*));

    int output_count = 0;

    st *stack = (st *)malloc(sizeof(st));

    create_empty_stack(stack);
    
    for (size_t i = 0; i < strlen(str); i++)
    {
        char op = str[i];

        switch (op)
        {
        case '(':
            push(stack,op);
            break;
        case ')':
            while (!is_empty(stack) && peek(stack) != '(')
            {
                output[output_count++] = pop(stack);                
            }
            pop(stack);
            break;
        case '+':           
        case '-':
        case '*':           
        case '/':
            while(!is_empty(stack) && precedence(op) <= precedence(peek(stack))){
                output[output_count++] = pop(stack);
            }
            push(stack,op);
            break;
        default:
            if (isdigit(op)){
                output[output_count++] = op;
            }
            break;
        }
    }

    while(!is_empty(stack)){
        if(peek(stack) == '(')
            exit(EXIT_FAILURE);
        output[output_count++] = pop(stack);
    }
    
    output[output_count++] = '\0';
    return output;
}
