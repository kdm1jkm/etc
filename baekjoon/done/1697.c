#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define LENGTH 100001

typedef struct _queue
{
    int data[LENGTH];
    int startIndex;
    int lastIndex;
} Queue;

Queue *newQueue()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->startIndex = 0;
    queue->lastIndex = 0;
    return queue;
}

void expendQueue(Queue *queue)
{
    if (++queue->lastIndex >= LENGTH)
        queue->lastIndex = 0;
}

void shrinkQueue(Queue *queue)
{
    if (++queue->startIndex >= LENGTH)
        queue->startIndex = 0;
}

void enqueue(Queue *queue, int data)
{
    queue->data[queue->lastIndex] = data;
    expendQueue(queue);
}

int dequeue(Queue *queue)
{
    int data = queue->data[queue->startIndex];
    shrinkQueue(queue);
    return data;
}

bool checkRange(int data)
{
    return 0 <= data && data < LENGTH;
}

int solve()
{
    int n, k;
    scanf("%d %d", &n, &k);

    int times[LENGTH];
    for (int i = 0; i < LENGTH; i++)
        times[i] = -1;
    times[n] = 0;

    Queue *queue = newQueue();
    enqueue(queue, n);

    while (true)
    {
        int idx = dequeue(queue);
        int newTime = times[idx] + 1;

        if (idx == k)
        {
            free(queue);
            return newTime - 1;
        }

        int newIndexes[] = {
            idx + 1,
            idx - 1,
            idx * 2};

        for (int i = 0; i < 3; i++)
        {
            if (!checkRange(newIndexes[i]))
                continue;

            if (times[newIndexes[i]] != -1)
                continue;

            if (newIndexes[i] == k)
            {
                free(queue);
                return newTime;
            }

            times[newIndexes[i]] = newTime;
            enqueue(queue, newIndexes[i]);
        }
    }
}

int main()
{
    printf("%d\n", solve());

    return 0;
}