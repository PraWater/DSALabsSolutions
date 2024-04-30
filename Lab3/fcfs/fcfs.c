#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

typedef struct process
{
    int pid;
    int arrival_time;
    int burst_time;
} Process;

Process pabtoe(int p, int a, int b);
Element itoe(int i);

int main()
{
    FILE *fp = fopen("fcfs_input.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }
    int n;
    fscanf(fp, "%d\n", &n);
    int p, a, b;
    Process *arr = (Process *)malloc(sizeof(Process) * n);
    Queue *q = createQueue();
    for (int i = 0; i < n; ++i)
    {
        fscanf(fp, "%d %d %d\n", &p, &a, &b);
        arr[i] = pabtoe(p, a, b);
    }
    int curr = -1;
    enqueue(q, itoe(0));
    for (int i = 0; !isEmpty(q) || curr != -1; ++i)
    {
        if (curr != -1)
        {
            --(arr[curr].burst_time);
            if (arr[curr].burst_time == 0)
            {
                printf("Process %d finished at time %d\n", arr[curr].pid, i);
                curr = -1;
            }
        }
        else
        {
            curr = front(q)->j;
            printf("Process %d started at time %d\n", arr[curr].pid, i);
            dequeue(q);
        }
        for (int j = 1 + curr; j < n; ++j)
        {
            if (arr[j].arrival_time == i)
            {
                enqueue(q, itoe(j));
                break;
            }
        }
    }
}

Process pabtoe(int p, int a, int b)
{
    Process e;
    e.pid = p;
    e.arrival_time = a;
    e.burst_time = b;
    return e;
}

Element itoe(int i)
{
    Element e;
    e.j = i;
    return e;
}