#include "element.h"
#include "stack.h"
#include "heap_usage.h"
#include <stdlib.h>

#define STACK_SIZE 1000

struct Stack
{
	int top;
	Element data[STACK_SIZE];
};

Stack *newStack()
{
	Stack *s = (Stack *)myalloc(sizeof(Stack));
	if(s != NULL)
		s->top = -1;
	return s;
}

bool push(Stack *s, Element e)
{
	if(s->top == STACK_SIZE - 1)
	return false;
	s->data[++(s->top)] = e;
	return true;
}

Element* pop (Stack *s)
{
	if (isEmpty(s)) return NULL;
	else {
		Element *a = &(s->data[(s->top)--]);
		return a;
	}
}

bool isEmpty (Stack *s)
{
	if (s->top == -1) return true;
	else return false;
}

Element* top (Stack *s)
{
	if (isEmpty(s)) return NULL;
	else {
		Element *a = &(s->data[(s->top)]);
		return a;
	}
}

void freeStack (Stack *s)
{
	myfree(s);
}