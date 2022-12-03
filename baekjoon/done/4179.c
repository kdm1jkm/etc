#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int MAP_TYPE;
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

#include <memory.h>

bool checkEscape(Map *map, Pos pos)
{
    return pos.row == 0 || pos.row == map->row - 1 || pos.column == 0 || pos.column == map->column - 1;
}

int main()
{
    int row, column;
    scanf("%d %d", &row, &column);

    Map *map = newMap(row, column);

    Pos jihoonPos;
    Queue *fireQueue = newQueue();
    for (int i = 0; i < row * column; i++)
    {
        char c;
        scanf(" %c", &c);
        switch (c)
        {
        case '#':
            map->data[i] = -1;
            break;

        case 'J':
            jihoonPos = indexToPos(map, i);
        case '.':
            map->data[i] = 0;
            break;

        case 'F':
            map->data[i] = 1;
            enqueue(fireQueue, indexToPos(map, i));
            break;
        }
    }

    printMap(map, printElementAsInteger);

    while (fireQueue->length > 0)
    {
        Pos fire = dequeue(fireQueue);
        int currentData = *getElement(map, fire);

        for (int i = 0; i < 4; i++)
        {
            Pos nextFire = addPos(fire, directions[i]);
            if (!checkRange(map, nextFire))
                continue;
            if (*getElement(map, nextFire) != 0)
                continue;

            enqueue(fireQueue, nextFire);
            *getElement(map, nextFire) = currentData + 1;
        }
    }

    freeQueue(fireQueue);

    printMap(map, printElementAsInteger);

    Map *escapeMap = newMap(row, column);
    memset(escapeMap->data, 0, sizeof(MAP_TYPE) * row * column);

    Queue *escapeQueue = newQueue();
    enqueue(escapeQueue, jihoonPos);
    *getElement(escapeMap, jihoonPos) = 1;

    bool escaped = false;

    while (escapeQueue->length > 0)
    {
        Pos pos = dequeue(escapeQueue);
        int current = *getElement(escapeMap, pos);

        if (checkEscape(map, pos))
        {
            escaped = true;
            printf("%d\n", current);
            break;
        }

        for (int i = 0; i < 4; i++)
        {
            Pos newPos = addPos(pos, directions[i]);
            if (!checkRange(map, newPos))
                continue;
            if (*getElement(map, newPos) == -1)
                continue;
            if (*getElement(escapeMap, newPos) != 0)
                continue;
            if (current + 1 >= *getElement(map, newPos) && *getElement(map, newPos) != 0)
                continue;

            *getElement(escapeMap, newPos) = current + 1;
            enqueue(escapeQueue, newPos);
        }
    }

    if (!escaped)
    {
        printf("IMPOSSIBLE\n");
    }

    printMap(escapeMap, printElementAsInteger);

    freeMap(map);
    freeMap(escapeMap);
    freeQueue(escapeQueue);
}