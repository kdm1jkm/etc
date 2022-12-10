#include <stdio.h>
#include <stdbool.h>

typedef struct _info
{
    int time, subin, sister;
} Info;

//******************************** Queue ***********************************

#include <stdlib.h>

typedef Info QUEUE_TYPE;

typedef struct _node
{
    QUEUE_TYPE data;
    struct _node *next;
} Node;

typedef struct _queue
{
    Node *start;
    Node *last;
    int length;
} Queue;

Queue *newQueue()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->start = queue->last = NULL;
    queue->length = 0;
    return queue;
}

void enqueue(Queue *queue, QUEUE_TYPE data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->data = data;

    if (queue->last == NULL)
        queue->start = queue->last = newNode;
    else
    {
        queue->last->next = newNode;
        queue->last = newNode;
    }

    queue->length++;
}

QUEUE_TYPE dequeue(Queue *queue)
{
    if (queue->length == 0)
    {
        printf("CANNOT REACH HERE!\n");
        exit(-1);
    }

    QUEUE_TYPE data = queue->start->data;

    Node *oldNode = queue->start;
    if (queue->length == 1)
    {
        queue->start = queue->last = NULL;
    }
    else
    {
        queue->start = queue->start->next;
    }
    free(oldNode);

    queue->length--;
    return data;
}

void emptyQueue(Queue *queue)
{
    while (queue->length > 0)
        dequeue(queue);
}

void freeQueue(Queue *queue)
{
    emptyQueue(queue);
    free(queue);
}

int subinNext(int subin, int i)
{
    switch (i)
    {
    case 0:
        return subin * 2;
    case 1:
        return subin - 1;
    case 2:
        return subin + 1;
    }
}

int main()
{
    int subin, sister;
    scanf("%d %d", &subin, &sister);

    Queue *queue = newQueue();
    enqueue(queue, (Info){0, subin, sister});

    while (true)
    {
        Info info = dequeue(queue);

        info.time++;
        info.sister += info.time;

        if (info.sister > 500000)
            continue;

        for (int i = 0; i < 3; i++)
        {
            info.subin = subinNext(info.subin, i);
            if (info.subin < 0 || info.subin > 500000)
                continue;
        }
    }
}