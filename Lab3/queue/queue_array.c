#include "element.h"
#include "queue.h"
#include <stdlib.h>

#define QUEUE_SIZE 1000

struct Queue
{
	int front;
	int size;
	Element data[QUEUE_SIZE];
};

Queue *createQueue()
{
	Queue *q = (Queue *)malloc(sizeof(Queue));
	if (q != NULL)
	{
		q->size = 0;
		q->front = 0;
	}
	return q;
}

bool enqueue(Queue *queue, Element element)
{
	if (queue->size == QUEUE_SIZE)
		return false;
	else
	{
		int rear = (queue->front + queue->size) % QUEUE_SIZE;
		++(queue->size);
		queue->data[rear] = element;
		return true;
	}
}

bool dequeue(Queue *queue)
{
	if (isEmpty(queue))
		return false;
	else
	{
		--(queue->size);
		++(queue->front);
		return true;
	}
}

Element *front(Queue *queue)
{
	if (isEmpty(queue))
		return NULL;
	else
	{
		return (queue->data) + queue->front;
	}
}

int size(Queue *queue)
{
	return queue->size;
}

bool isEmpty(Queue *queue)
{
	return queue->size == 0;
}

void destroyQueue(Queue *queue)
{
	free(queue);
}