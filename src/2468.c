#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>

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

typedef Pos QUEUE_TYPE;
typedef struct _queue
{
    QUEUE_TYPE *data;
    int capacity;
    int startIndex, endIndex;
} Queue;

Queue *newQueue(int capacity)
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->startIndex = queue->endIndex = 0;
    queue->capacity = capacity;
    queue->data = (QUEUE_TYPE *)malloc(sizeof(QUEUE_TYPE) * capacity);
    return queue;
}

void freeQueue(Queue *queue)
{
    free(queue->data);
    free(queue);
}

void enqueue(Queue *queue, Pos data)
{
    queue->data[queue->endIndex] = data;
    if (++queue->endIndex == queue->capacity)
        queue->endIndex = 0;
}

QUEUE_TYPE dequeue(Queue *queue)
{
    QUEUE_TYPE data = queue->data[queue->startIndex];
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

void copyMap(Map *dest, Map *source)
{
    memcpy(dest->data, source->data, sizeof(int) * dest->row * dest->column);
}

// criteria 이하의 지점은 물에 잠김
// -1은 물에 잠김, 0은 안잠김
void check(Map *map, int criteria)
{
    for (int i = 0; i < map->row * map->column; i++)
    {
        int newData;
        if (map->data[i] > criteria)
            newData = 0;
        else
            newData = -1;

        map->data[i] = newData;
    }
}

// 0인 지점을 1로 칠하고 칠한 갯수 반환
int fill(Map *map, Pos startPos)
{
    if (*getElement(map, startPos) != 0)
        return 0;

    int sum = 1;

    Queue *queue = newQueue(map->row * map->column);
    enqueue(queue, startPos);
    *getElement(map, startPos) = 1;

    while (queueSize(queue) > 0)
    {
        Pos pos = dequeue(queue);
        for (int i = 0; i < 4; i++)
        {
            Pos nextPos = addPos(pos, directions[i]);
            if (!checkRange(map, nextPos))
                continue;
            if (*getElement(map, nextPos) != 0)
                continue;
            *getElement(map, nextPos) = 1;
            enqueue(queue, nextPos);
            sum += 1;
        }
    }

    freeQueue(queue);

    return sum;
}

int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }

int main()
{
    int n;
    scanf("%d", &n);

    Map *originalMap = newMap(n, n);
    int minHeight = 100, maxHeight = 1;
    for (int i = 0; i < n * n; i++)
    {
        scanf("%d", &originalMap->data[i]);
        minHeight = min(minHeight, originalMap->data[i]);
        maxHeight = max(maxHeight, originalMap->data[i]);
    }

    Map *map = newMap(n, n);

    int maxSafeArea = 0;
    for (int height = minHeight - 1; height <= maxHeight; height++)
    {
        copyMap(map, originalMap);
        check(map, height);
        int safeArea = 0;
        for (int row = 0; row < originalMap->row; row++)
        {
            for (int column = 0; column < originalMap->column; column++)
            {
                int filled = fill(map, (Pos){.row = row, .column = column});
                if (filled > 0)
                    safeArea++;
            }
        }
        maxSafeArea = max(maxSafeArea, safeArea);
    }

    printf("%d\n", maxSafeArea);

    freeMap(originalMap);
    freeMap(map);
}