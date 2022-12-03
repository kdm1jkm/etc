#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _map
{
    int *data;
    int row, column;
} Map;

typedef struct _pos
{
    int row, column;
} Pos;

Map *newMap(int row, int column)
{
    Map *map = (Map *)malloc(sizeof(Map));

    map->row = row;
    map->column = column;

    map->data = (int *)malloc(sizeof(int) * row * column);

    return map;
}

void freeMap(Map *map)
{
    free(map->data);
    free(map);
}

const Pos directions[4] = {
    {.row = 1, .column = 0},
    {.row = -1, .column = 0},
    {.row = 0, .column = 1},
    {.row = 0, .column = -1}};

Pos indexToPos(Map *map, int index)
{
    return (Pos){.row = index / map->column, .column = index % map->column};
}

int posToIndex(Map *map, Pos pos)
{
    return pos.row * map->column + pos.column;
}

int *getElement(Map *map, Pos pos)
{
    return &map->data[pos.column + pos.row * map->column];
}

bool checkRange(Map *map, Pos pos)
{
    return 0 <= pos.row && pos.row < map->row && 0 <= pos.column && pos.column < map->column;
}

Pos addPos(Pos pos1, Pos pos2)
{
    return (Pos){.row = pos1.row + pos2.row, .column = pos1.column + pos2.column};
}

void printMap(Map *map)
{
    return;
    puts("--------------");
    for (int row = 0; row < map->row; row++)
    {
        for (int column = 0; column < map->column; column++)
            printf("%d ", *getElement(map, (Pos){row, column}));
        putchar('\n');
    }
    puts("--------------");
}

typedef struct _queue
{
    int *data;
    int capacity;
    int startIndex, endIndex;
} Queue;

Queue *newQueue(int capacity)
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->startIndex = queue->endIndex = 0;
    queue->capacity = capacity;
    queue->data = (int *)malloc(sizeof(int) * capacity);
    return queue;
}

void freeQueue(Queue *queue)
{
    free(queue->data);
    free(queue);
}

void enqueue(Queue *queue, int data)
{
    queue->data[queue->endIndex] = data;
    if (++queue->endIndex == queue->capacity)
        queue->endIndex = 0;
}

int dequeue(Queue *queue)
{
    int data = queue->data[queue->startIndex];
    if (++queue->startIndex == queue->capacity)
        queue->startIndex = 0;
    return data;
}

int queueSize(Queue *queue)
{
    if (queue->startIndex <= queue->endIndex)
        return queue->endIndex - queue->startIndex;

    return queue->capacity - (queue->startIndex - queue->endIndex);
}

int main()
{
    int row, column;
    scanf("%d %d", &column, &row);
    Map *map = newMap(row, column);

    for (int i = 0; i < row * column; i++)
        scanf("%d", &map->data[i]);

    Queue *queue = newQueue(row * column);

    for (int i = 0; i < row * column; i++)
    {
        if (map->data[i] != 1)
            continue;
        enqueue(queue, i);
    }

    while (queueSize(queue) > 0)
    {
        int index = dequeue(queue);
        Pos currentPos = indexToPos(map, index);
        int currentData = *getElement(map, currentPos);

        for (int i = 0; i < 4; i++)
        {
            Pos nextPos = addPos(currentPos, directions[i]);
            if (!checkRange(map, nextPos))
                continue;

            int data = *getElement(map, nextPos);
            if (data != 0)
                continue;

            *getElement(map, nextPos) = currentData + 1;
            enqueue(queue, posToIndex(map, nextPos));
        }
    }

    int max = 0;
    for (int i = 0; i < row * column; i++)
    {
        if (map->data[i] == 0)
        {
            printf("-1\n");
            freeQueue(queue);
            freeMap(map);
            return 0;
        }
        max = max > map->data[i] ? max : map->data[i];
    }

    printf("%d\n", max - 1);

    freeQueue(queue);
    freeMap(map);
}