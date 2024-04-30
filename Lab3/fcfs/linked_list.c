#include "element.h"
#include "linked_list.h"
#include <stdlib.h>

LIST createNewList()
{
	LIST list = (LIST)malloc(sizeof(linked_list));
	if (list != NULL)
	{
		list->count = 0;
	}
	return list;
}

NODE createNewNode(Element data)
{
	NODE n = (NODE)malloc(sizeof(node));
	if (n != NULL)
	{
		n->next = NULL;
		n->data = data;
	}
	return n;
}

void insertNodeIntoList(NODE node, LIST list)
{
	if (list->count == 0)
	{
		list->head = node;
		list->tail = node;
		node->next = NULL;
	}
	else
	{
		node->next = list->head;
		list->head = node;
	}
	++(list->count);
}

bool removeFirstNode(LIST list)
{
	if (list->count == 0)
		return false;
	--(list->count);
	NODE n = list->head;
	list->head = n->next;
	free(n);
	return true;
}

void insertNodeAtEnd(NODE node, LIST list)
{
	if (list->count == 0)
	{
		list->head = node;
		list->tail = node;
	}
	else
	{
		list->tail->next = node;
		list->tail = node;
	}
	++(list->count);
}

void destroyList(LIST list)
{
	NODE n = list->head;
	NODE n1 = n->next;
	while (n != NULL)
	{
		n1 = n->next;
		free(n);
		n = n1;
	}
	free(list);
}