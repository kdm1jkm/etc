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

// Return Count
int paint(int *data, int index, int rowSize, int columnSize)
{
    if (data[index] != 1)
        return 0;

    data[index] = 2;

    Point point = getPoint(index, columnSize);

    Point newPoints[] = {
        {.row = point.row + 1, .column = point.column},
        {.row = point.row - 1, .column = point.column},
        {.row = point.row, .column = point.column + 1},
        {.row = point.row, .column = point.column - 1}};

    int sum = 1;

    for (int i = 0; i < 4; i++)
    {
        if (!checkRange(newPoints[i], rowSize, columnSize))
            continue;

        if (data[getIndex(newPoints[i], columnSize)] != 1)
            continue;

        sum += paint(data, getIndex(newPoints[i], columnSize), rowSize, columnSize);
    }

    return sum;
}

int main()
{
    int row, column;
    scanf("%d %d", &row, &column);

    int *data = (int *)malloc(sizeof(int) * row * column);

    for (int i = 0; i < row * column; i++)
        scanf("%d", &data[i]);

    int pictureCount = 0;
    int biggestSize = 0;

    for (int i = 0; i < row * column; i++)
    {
        int size = paint(data, i, row, column);
        if (size == 0)
            continue;

        pictureCount++;
        if (size > biggestSize)
            biggestSize = size;
    }

    printf("%d\n%d\n", pictureCount, biggestSize);
}