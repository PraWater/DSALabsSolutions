#include "linked_list.h"
#include "stack.h"
#include <stdlib.h>

struct Stack
{
	linked_list *list;
};

Stack *newStack()
{
	Stack *s = (Stack *)malloc(sizeof(Stack));
	if (s != NULL)
		s->list = createNewList();
	return s;
}

bool push(Stack *stack, float element)
{
	NODE n = createNewNode(element);
	if (n != NULL)
	{
		insertNodeIntoList(n, stack->list);
		return true;
	}
	else
		return false;
}

float top(Stack *stack)
{
	if (isEmpty(stack))
		return -1;
	else
		return (((stack->list)->head)->data);
}

float pop(Stack *stack)
{
	if (isEmpty(stack))
		return -1;
	else
	{
		float ele = (((stack->list)->head)->data);
		removeFirstNode(stack->list);
		return ele;
	}
}

bool isEmpty(Stack *stack)
{
	if ((stack->list)->count == 0)
		return true;
	else
		return false;
}

void freeStack(Stack *stack)
{
	destroyList(stack->list);
	free(stack);
}