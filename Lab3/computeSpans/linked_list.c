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

NODE createNewNode(int data)
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
		node->next = NULL;
	}
	else
	{
		node->next = list->head;
		list->head = node;
	}
	++(list->count);
}

void removeFirstNode(LIST list)
{
	if (list->count == 0)
		return;
	--(list->count);
	NODE n = list->head;
	list->head = n->next;
	free(n);
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