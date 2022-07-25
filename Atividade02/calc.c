#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "calc.h"

#define MAX 100

// Creating a stack
struct stack
{
    double items[MAX];
    int top;
};

typedef struct stack st;

void d_create_empty_stack(st *s)
{
    s->top = -1;
}

// Check if the stack is full
int d_is_full(st *s)
{
    if (s->top == MAX - 1)
        return 1;
    else
        return 0;
}

// Check if the stack is empty
int d_is_empty(st *s)
{
    if (s->top == -1)
        return 1;
    else
        return 0;
}

// Add elements into stack
void d_push(st *s, double new_item)
{
    if (d_is_full(s))
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
double d_pop(st *s)
{
    double ret;

    if (d_is_empty(s))
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

double d_peek(st *s)
{
    double ret;

    if (d_is_empty(s))
    {
        printf("\n STACK EMPTY \n");
    }
    else
    {
        ret = s->items[s->top];
    }
    return ret;
}

double calculate(char *str)
{
    
    st *stack = (st *)malloc(sizeof(st));
    d_create_empty_stack(stack);

    for (size_t i = 0; i < strlen(str); i++)
    {
        char op = str[i];
        if (isdigit(op))
        {
            d_push(stack, atof(&op));
        }
        else
        {

            double right = d_pop(stack);
            double left = d_pop(stack);
            switch (op)
            {
            case '+':
                d_push(stack, left + right);
                break;
            case '-':
                d_push(stack, left - right);
                break;
            case '*':
                d_push(stack, left * right);
                break;
            case '/':
                d_push(stack, left / right);
                break;
            default:
                break;
            }
        }
    }
    
    return d_pop(stack);
}
