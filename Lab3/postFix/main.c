#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

int main()
{
    char str[30];
    printf("Input string: ");
    scanf("%[^\n]", str);
    Stack *stack = newStack();
    char *tok;
    const char space[2] = " ";
    tok = strtok(str, space);
    while (tok != NULL)
    {
        if (strcmp(tok, "+") == 0)
        {
            float x = pop(stack);
            float y = pop(stack);
            push(stack, x + y);
        }
        else if (strcmp(tok, "-") == 0)
        {
            float x = pop(stack);
            float y = pop(stack);
            push(stack, y - x);
        }
        else if (strcmp(tok, "*") == 0)
        {
            float x = pop(stack);
            float y = pop(stack);
            push(stack, x * y);
        }
        else if (strcmp(tok, "/") == 0)
        {
            float x = pop(stack);
            float y = pop(stack);
            push(stack, y / x);
        }
        else
        {
            push(stack, atof(tok));
        }
        tok = strtok(NULL, space);
    }
    printf("Answer is: %f", pop(stack));
    return 0;
}