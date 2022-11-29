#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _pos Pos;

typedef int MAP_TYPE;
typedef Pos QUEUE_TYPE;

typedef struct _map
{
    MAP_TYPE *data;
    int row, column, height;
} Map;

typedef struct _pos
{
    int row, column, height;
} Pos;

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
    return (Pos){.row = pos1.row + pos2.row, .column = pos1.column + pos2.column, .height = pos1.height + pos2.height};
}

Pos scalarVec(const Pos *vec, int scale)
{
    return (Pos){vec->row * scale, vec->column * scale, vec->height * scale};
}

int comparePos(const void *p1, const void *p2)
{
    Pos *pos1 = (Pos *)p1;
    Pos *pos2 = (Pos *)p2;
    if (pos1->row == pos2->row)
    {
        if (pos1->column == pos2->column)
        {
            return pos1->height - pos2->height;
        }
        return pos1->column - pos2->column;
    }
    return pos1->row - pos2->row;
}

//**************************************************************************
//                                  Map

Map *newMap(int row, int column, int height)
{
    Map *map = (Map *)malloc(sizeof(Map));

    map->row = row;
    map->column = column;
    map->height = height;

    map->data = (MAP_TYPE *)malloc(sizeof(MAP_TYPE) * row * column * height);

    return map;
}

void freeMap(Map *map)
{
    free(map->data);
    free(map);
}

const Pos directions[6] = {
    {.row = 1, .column = 0, .height = 0},
    {.row = -1, .column = 0, .height = 0},
    {.row = 0, .column = 1, .height = 0},
    {.row = 0, .column = -1, .height = 0},
    {.row = 0, .column = 0, .height = 1},
    {.row = 0, .column = 0, .height = -1},
};

Pos indexToPos(Map *map, int index)
{
    Pos pos;
    pos.column = index % map->column;
    index /= map->column;
    pos.row = index % map->row;
    index /= map->row;
    pos.height = index % map->height;
    return pos;
}

int posToIndex(Map *map, Pos pos)
{
    int index = 0;
    index *= map->height;
    index += pos.height;
    index *= map->row;
    index += pos.row;
    index *= map->column;
    index += pos.column;
    return index;
}

MAP_TYPE *getElement(Map *map, Pos pos)
{
    return &map->data[posToIndex(map, pos)];
}

bool checkRange(Map *map, Pos pos)
{
    return 0 <= pos.row && pos.row < map->row &&
           0 <= pos.column && pos.column < map->column &&
           0 <= pos.height && pos.height < map->height;
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
//                                  Debug

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

//**************************************************************************
//                                  Main

int main()
{
    int m, n, h;
    scanf("%d %d %d", &m, &n, &h);
    Map *map = newMap(n, m, h);

    for (int i = 0; i < n * m * h; i++)
        scanf("%d", &map->data[i]);

    Queue *queue = newQueue();

    for (int i = 0; i < n * m * h; i++)
    {
        if (map->data[i] == 1)
            enqueue(queue, indexToPos(map, i));
    }

    while (queue->length > 0)
    {
        Pos pos = dequeue(queue);
        int current = *getElement(map, pos);

        for (int i = 0; i < 6; i++)
        {
            Pos newPos = addPos(pos, directions[i]);
            if (!checkRange(map, newPos))
                continue;
            int *element = getElement(map, newPos);
            if (*element != 0)
                continue;
            *element = current + 1;
            enqueue(queue, newPos);
        }
    }

    int max = 0;

    for (int i = 0; i < n * m * h; i++)
    {
        if (map->data[i] == 0)
        {
            max = 0;
            break;
        }
        if (map->data[i] > max)
            max = map->data[i];
    }

    printf("%d\n", max - 1);

    freeQueue(queue);
    freeMap(map);

    return 0;
}