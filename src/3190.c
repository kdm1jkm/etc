#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>

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

Map *mapClone(Map *originalMap)
{
    Map *map = newMap(originalMap->row, originalMap->column);
    for (int i = 0; i < map->row * map->column; i++)
        map->data[0] = originalMap->data[0];
    return map;
}

void freeMap(Map *map)
{
    free(map->data);
    free(map);
}

const Pos directions[4] = {
    {.row = 0, .column = 1},
    {.row = -1, .column = 0},
    {.row = 0, .column = -1},
    {.row = 1, .column = 0},
};

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

int has_apple(Pos *apples, int appleCount, Pos pos)
{
    for (int i = 0; i < appleCount; i++)
    {
        if (apples[i].row == pos.row && apples[i].column == pos.column)
            return i;
    }

    return -1;
}

bool is_failed(Queue *snake, int size)
{
    Pos headPos = snake->last->data;
    if (headPos.row < 0 || headPos.row >= size || headPos.column < 0 || headPos.column >= size)
        return true;
    Node *current = snake->start;
    for (int i = 0; i < snake->length - 1; i++)
    {
        Pos pos = current->data;
        if (pos.row == headPos.row && pos.column == headPos.column)
            return true;
        current = current->next;
    }
    return false;
}

typedef struct
{
    int time;
    char direction;
} Control;

bool is_snake(Queue *snake, Pos pos)
{
    Node *node = snake->start;
    for (int i = 0; i < snake->length; i++)
    {
        if (node->data.row == pos.row && node->data.column == pos.column)
            return true;
        node = node->next;
    }
    return false;
}

void printState(Pos *apples, int appleCount, Queue *snake, int n)
{
    return;
    puts("======================");
    for (int row = 0; row < n; row++)
    {
        for (int column = 0; column < n; column++)
        {
            if (has_apple(apples, appleCount, (Pos){row, column}) != -1)
                putchar('A');
            else if (is_snake(snake, (Pos){row, column}))
                putchar('s');
            else
                putchar('.');
        }
        putchar('\n');
    }
    puts("======================");
}

int main(void)
{
    int n, k, l;
    scanf("%d", &n);

    scanf("%d", &k);
    Pos *apples = (Pos *)malloc(sizeof(Pos) * k);
    for (int i = 0; i < k; i++)
    {
        int r, c;
        scanf("%d %d", &r, &c);
        apples[i] = (Pos){r - 1, c - 1};
    }

    scanf("%d", &l);
    Control *controls = (Control *)malloc(sizeof(Control) * l);
    for (int i = 0; i < l; i++)
        scanf("%d %c", &controls[i].time, &controls[i].direction);

    int currentDirection = 0;

    Queue *snake = newQueue();
    enqueue(snake, (Pos){0, 0});

    int controlIndex = 0;
    int nextControlTime = controls[0].time;

    int currentTime = 0;
    while (!is_failed(snake, n))
    {
        printState(apples, k, snake, n);
        if (currentTime == nextControlTime)
        {
            if (controls[controlIndex].direction == 'D')
                currentDirection -= 1;
            else
                currentDirection += 1;
            currentDirection = (currentDirection + 4) % 4;
            if (controlIndex == l - 1)
                nextControlTime = -1;
            else
                nextControlTime = controls[++controlIndex].time;
        }

        Pos nextPos = addPos(snake->last->data, directions[currentDirection]);
        int appleI = has_apple(apples, k, nextPos);
        enqueue(snake, nextPos);

        if (is_failed(snake, n))
        {
            currentTime += 1;
            break;
        }

        if (appleI == -1)
            dequeue(snake);
        else
            apples[appleI] = (Pos){-1, -1};

        currentTime += 1;
    }
    printState(apples, k, snake, n);

    printf("%d\n", currentTime);

    free(apples);
    free(controls);
    freeQueue(snake);
}