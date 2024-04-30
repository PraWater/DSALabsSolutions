// Include the stack implementation in your code. You can use either the linked list implementation or the array implementation.
#include <stdio.h>
#include "stack.h"

void computeSpans(int *inputs, int *spans, int n);

int main()
{
    int inputs[] = {6, 3, 4, 5, 2};
    int spans[5];
    computeSpans(inputs, spans, 5);
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", spans[i]);
    }
    printf("\n");
    int inputs2[] = {100, 80, 60, 70, 60, 75, 85};
    int spans2[7];
    computeSpans(inputs2, spans2, 7);
    for (int i = 0; i < 7; i++)
    {
        printf("%d ", spans2[i]);
    }
    printf("\n");
    return 0;
}

void computeSpans(int *inputs, int *spans, int n)
{
    /*
        Write your code here
    */
    Stack *stack = newStack();
    spans[0] = 1;
    push(stack, 0);
    for (int i = 1; i < n; ++i)
    {
        while (inputs[i] >= inputs[top(stack)])
        {
            pop(stack);
        }
        spans[i] = i - top(stack);
        push(stack, i);
    }
}