#include "linked_list.h"
#include "stack.h"
#include "heap_usage.h"
#include <stdlib.h>

struct Stack
{
	linked_list *list;
};

Stack *newStack()
{
	Stack *s = (Stack *)myalloc(sizeof(Stack));
	if(s != NULL)
		s->list = createNewList();
	return s;
}

bool push(Stack *stack, Element element)
{
	NODE n = createNewNode(element);
	if (n != NULL)
	{
		insertNodeIntoList(n, stack->list);
		return true;
	}
	else return false;
}

Element *top(Stack *stack)
{
	if (isEmpty(stack)) return NULL;
	else return &(((stack->list)->head)->data);
}

Element *pop(Stack *stack)
{
	if (isEmpty(stack)) return NULL;
	else {
		Element *ele = &(((stack->list)->head)->data);
		removeFirstNode(stack->list);
		return ele;
	}
}

bool isEmpty(Stack *stack)
{
	if ((stack->list)->count == 0) return true;
	else return false;
}

void freeStack(Stack *stack)
{
	destroyList(stack->list);
	myfree(stack);
}