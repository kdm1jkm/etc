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

//********************************* Map ************************************

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

const Pos directions[4] = {
    {.row = 0, .column = 1},
    {.row = -1, .column = 0},
    {.row = 0, .column = -1},
    {.row = 1, .column = 0},
};
