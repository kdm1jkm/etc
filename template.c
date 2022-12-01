#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _pos Pos;

typedef int MAP_TYPE;
typedef int LIST_TYPE;
typedef Pos QUEUE_TYPE;

typedef struct _map
{
    MAP_TYPE *data;
    int row, column;
} Map;

typedef struct _pos
{
    int row, column;
} Pos;

typedef struct _arrayList
{
    LIST_TYPE *data;
    size_t capacity;
    size_t size;
} ArrayList;

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

//**************************************************************************
//                                  Pos

Pos addPos(Pos pos1, Pos pos2)
{
    return (Pos){.row = pos1.row + pos2.row, .column = pos1.column + pos2.column};
}

Pos scalarVec(const Pos *vec, int scale)
{
    return (Pos){vec->row * scale, vec->column * scale};
}

int comparePos(const void *p1, const void *p2)
{
    Pos *pos1 = (Pos *)p1;
    Pos *pos2 = (Pos *)p2;
    if (pos1->row == pos2->row)
        return pos1->column - pos2->column;
    return pos1->row - pos2->row;
}

//**************************************************************************
//                                  Map

Map *newMap(int row, int column)
{
    Map *map = (Map *)malloc(sizeof(Map));

    map->row = row;
    map->column = column;

    map->data = (MAP_TYPE *)malloc(sizeof(MAP_TYPE) * row * column);

    return map;
}

Map *mapClone(Map *originalMap)
{
    Map *map = newMap(originalMap->row, originalMap->column);
    for (int i = 0; i < map->row * map->column; i++)
        map->data[i] = originalMap->data[i];
    return map;
}

void freeMap(Map *map)
{
    free(map->data);
    free(map);
}

void fillMap(Map *map, MAP_TYPE element)
{
    for (int i = 0; i < map->row * map->column; i++)
        map->data[i] = element;
}

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

//**************************************************************************
//                                  Queue

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

//**************************************************************************
//                                  List

ArrayList *newArrayList(size_t capacity)
{
    ArrayList *arrayList = (ArrayList *)malloc(sizeof(ArrayList));

    arrayList->capacity = capacity;
    arrayList->data = malloc(sizeof(LIST_TYPE) * capacity);
    arrayList->size = 0;

    return arrayList;
}

void freeArrayList(ArrayList *arrayList)
{
    free(arrayList->data);
    free(arrayList);
}

void sortList(ArrayList *arrayList, int compare(const void *, const void *))
{
    qsort(arrayList->data, arrayList->size, sizeof(LIST_TYPE), compare);
}

LIST_TYPE *getListElement(ArrayList *arrayList, size_t index)
{
    return &arrayList->data[index];
}

bool resetListCapacity(ArrayList *arrayList, size_t capacity)
{
    void *prev = arrayList->data;
    arrayList->data = realloc(arrayList->data, sizeof(LIST_TYPE) * capacity);
    if (arrayList->data == NULL)
    {
        arrayList->data = prev;
        return false;
    }
    return true;
}

bool listAppend(ArrayList *arrayList, LIST_TYPE element)
{
    if (arrayList->size == arrayList->capacity)
        if (!resetListCapacity(arrayList, arrayList->capacity * 2))
            return false;

    *getListElement(arrayList, arrayList->size++) = element;

    return true;
}

void *findElement(ArrayList *arrayList, void *element, int compare(const void *, const void *))
{
    return bsearch(element, arrayList->data, arrayList->size, sizeof(LIST_TYPE), compare);
}

//**************************************************************************
//                                  Debug

void printElementAsInteger(int a)
{
    printf("%d ", a);
}

void printMap(Map *map, void (*printElement)(MAP_TYPE))
{
#ifdef ONLINE_JUDGE
    return;
#endif
    puts("--------------");
    for (int row = 0; row < map->row; row++)
    {
        for (int column = 0; column < map->column; column++)
            printElement(*getElement(map, (Pos){row, column}));
        putchar('\n');
    }
    puts("--------------");
}

//**************************************************************************
//                                  Util

int max(int a, int b)
{
    return a > b ? a : b;
}

int abs(int a)
{
    return a > 0 ? a : -a;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

const Pos directions[4] = {
    {.row = 0, .column = 1},
    {.row = -1, .column = 0},
    {.row = 0, .column = -1},
    {.row = 1, .column = 0},
};
