#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char MAP_TYPE;
typedef struct _map
{
    MAP_TYPE *data;
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

    map->data = (MAP_TYPE *)malloc(sizeof(MAP_TYPE) * row * column);

    return map;
}

Map *mapClone(Map *map)
{
    Map *newMap = newMap(map->row, map->column);
    for (int i = 0; i < map->row * map->column; i++)
        newMap->data[0] = map->data[0];
    return newMap;
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

MAP_TYPE *getElement(Map *map, Pos pos)
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

void printElementAsInteger(int a)
{
    printf("%d ", a);
}

void printMap(Map *map, void (*printElement)(MAP_TYPE))
{
    return;
    puts("--------------");
    for (int row = 0; row < map->row; row++)
    {
        for (int column = 0; column < map->column; column++)
            printElement(*getElement(map, (Pos){row, column}));
        putchar('\n');
    }
    puts("--------------");
}

typedef Pos QUEUE_TYPE;
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

void enqueue(Queue *queue, Pos data)
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

/************************************************************************/

int fill(Map *map, Pos startPos)
{
    char c = *getElement(map, startPos);
    *getElement(map, startPos) = ' ';
    Queue *queue = newQueue();
    enqueue(queue, startPos);

    int result = 1;

    while (queue->length > 0)
    {
        Pos pos = dequeue(queue);

        for (int i = 0; i < 4; i++)
        {
            Pos nextPos = addPos(pos, directions[i]);
            if (!checkRange(map, nextPos))
                continue;
            if (*getElement(map, nextPos) != c)
                continue;

            enqueue(queue, nextPos);
            *getElement(map, nextPos) = ' ';
            result++;
        }
    }

    freeQueue(queue);

    return result;
}

int main()
{
    int n;
    Map *map = newMap(n, n);
    for (int i = 0; i < n * n; i++)
        scanf(" %c", &map->data[i]);

    Map *RGMap = mapClone(map);
    for (int i = 0; i < n * n; i++)
        if (RGMap->data[i] == 'R')
            RGMap->data[i] = 'G';

    for (int i = 0; i < n * n; i++)
    {
    }

    freeMap(map);
    freeMap(RGMap);
}