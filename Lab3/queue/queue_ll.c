#include "queue.h"
#include "linked_list.h"
#include <stdlib.h>

struct Queue
{
    LIST list;
};

Queue *createQueue()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    if (q != NULL)
    {
        q->list = createNewList();
    }
    return q;
}

bool enqueue(Queue *queue, Element element)
{
    NODE n = createNewNode(element);
    if (n == NULL)
        return false;
    insertNodeAtEnd(n, queue->list);
    return true;
}

bool dequeue(Queue *queue)
{
    return removeFirstNode(queue->list);
}

Element *front(Queue *queue)
{
    return &(queue->list->head->data);
}

int size(Queue *queue)
{
    return queue->list->count;
}

bool isEmpty(Queue *queue)
{
    return queue->list->count == 0;
}

void destroyQueue(Queue *queue)
{
    destroyList(queue->list);
    free(queue);
}