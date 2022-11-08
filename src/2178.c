#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _point
{
    int row, column;
} Point;

Point getPoint(int index, int columnSize)
{
    return (Point){.row = index / columnSize, .column = index % columnSize};
}

int getIndex(Point point, int columnSize)
{
    return point.row * columnSize + point.column;
}

bool checkRange(Point point, int rowSize, int columnSize)
{
    return 0 <= point.row && point.row < rowSize && 0 <= point.column && point.column < columnSize;
}

typedef struct _node
{
    struct _node *next;
    int value;
} Node;

typedef struct _queue
{
    Node *front;
    Node *back;
    int size;
} Queue;

Queue *newQueue()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->back = NULL;
    queue->size = 0;

    return queue;
}

void freeQueue(Queue *queue)
{
    free(queue);
}

void enqueue(Queue *queue, int value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->value = value;

    if (queue->size++ == 0)
    {
        queue->front = newNode;
        queue->back = newNode;
    }
    else
    {
        queue->back->next = newNode;
        queue->back = newNode;
    }
}

int dequeue(Queue *queue)
{
    if (queue->size <= 0)
    {
        printf("CANNOT REACH HERE!\n");
        exit(EXIT_FAILURE);
    }

    Node *oldNode = queue->front;
    int value = oldNode->value;

    queue->front = queue->front->next;
    queue->size--;

    free(oldNode);
    return value;
}

void printdata(int *data, int row, int column)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            printf("%3d", data[getIndex((Point){.row = i, .column = j}, column)]);
        }
        putchar('\n');
    }
    putchar('\n');
}

int main()
{
    int row, column;
    scanf("%d %d", &row, &column);

    int *data = (int *)malloc(sizeof(int) * row * column);

    for (int i = 0; i < row * column; i++)
    {
        char c;
        scanf(" %c", &c);
        data[i] = (c - '0') - 1;
        // 0은 아직 안 지난 곳
        // -1은 벽
    }
    // printdata(data, row, column);

    Queue *queue = newQueue();
    enqueue(queue, 0);
    data[0] = 1;

    while (queue->size > 0)
    {
        int currentIndex = dequeue(queue);
        Point currentPoint = getPoint(currentIndex, column);
        int currentValue = data[currentIndex];

        if (currentIndex == row * column - 1)
        {
            // printdata(data, row, column);

            printf("%d\n", currentValue);
            freeQueue(queue);
            return 0;
        }

        Point newPoints[] = {
            {.row = currentPoint.row + 1, .column = currentPoint.column},
            {.row = currentPoint.row - 1, .column = currentPoint.column},
            {.row = currentPoint.row, .column = currentPoint.column + 1},
            {.row = currentPoint.row, .column = currentPoint.column - 1}};

        for (int i = 0; i < 4; i++)
        {
            if (!checkRange(newPoints[i], row, column))
                continue;

            int index = getIndex(newPoints[i], column);

            if (data[index] != 0)
                continue;

            data[index] = currentValue + 1;
            enqueue(queue, index);
        }
    }

    freeQueue(queue);
}