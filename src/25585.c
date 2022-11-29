#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

const int INT_INF = INT_MAX;

typedef struct _pos
{
    int row, column;
} Pos;

Pos posFromIndex(int index, int columnSize)
{
    return (Pos){.row = index / columnSize, .column = index % columnSize};
}

bool isCatchable(Pos pos1, Pos pos2)
{
    return (pos1.row + pos1.column) % 2 == (pos2.row + pos2.column) % 2;
}

typedef struct _matrix
{
    int row, column;
    int *data;
} Matrix;

Matrix *newMatrix(int row, int column)
{
    Matrix *matrix = (Matrix *)malloc(sizeof(Matrix));

    matrix->row = row;
    matrix->column = column;
    matrix->data = (int *)malloc(sizeof(int) * row * column);

    return matrix;
}

void fillMatrix(Matrix *matrix, int value)
{
    for (int i = 0; i < matrix->row * matrix->column; i++)
        matrix->data[i] = value;
}

int *getElement(Matrix *matrix, Pos pos)
{
    return &matrix->data[pos.column + pos.row * matrix->column];
}

void freeMatrix(Matrix *matrix)
{
    free(matrix->data);
    free(matrix);
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int abs(int a)
{
    return a > 0 ? a : -a;
}

int calc(Matrix *matrix, Matrix *distanceMatrix, int from, int to)
{
    int value = *getElement(matrix, (Pos){from, to});
    if (value != -1)
        return value;

    if (to == 0)
    {
        *getElement(matrix, (Pos){from, to}) = 0;
        return 0;
    }

    value = INT_INF;

    for (int i = 0; i < matrix->row; i++)
    {
        // to에 포함되지 않은 경우
        if (((1 << i) & to) == 0)
            continue;

        int newTo = to ^ (1 << i);

        int newValue =
            *getElement(distanceMatrix, (Pos){from, i}) +
            calc(matrix, distanceMatrix, i, newTo);
        if (newValue < value)
            value = newValue;
    }

    return value;
}

int main()
{
    int n;
    scanf("%d", &n);

    Pos player;

    Pos enemies[10];
    int enemyCount = 0;

    // 입력
    for (int i = 0; i < n * n; i++)
    {
        int a;
        scanf("%d", &a);
        if (a == 1)
            enemies[enemyCount++] = posFromIndex(i, n);
        else if (a == 2)
            player = posFromIndex(i, n);
    }

    // 잡을 수 있는지 검사
    for (int i = 0; i < enemyCount; i++)
    {
        if (!isCatchable(enemies[i], player))
        {
            printf("Shorei\n");
            return 0;
        }
    }
    printf("Undertaker\n");

    // 인접행렬 구하기(적 끼리 거리)
    Matrix *distanceMatrix = newMatrix(enemyCount + 1, enemyCount + 1);
    fillMatrix(distanceMatrix, 0);
    for (int from = 0; from < enemyCount; from++)
    {
        for (int to = from + 1; to < enemyCount; to++)
        {
            int distance = max(
                abs(enemies[from].row - enemies[to].row),
                abs(enemies[to].column - enemies[to].column));
            *getElement(distanceMatrix, (Pos){from, to}) = distance;
            *getElement(distanceMatrix, (Pos){to, from}) = distance;
        }
    }

    // 시작지점 관련된 인접행렬(단방향 그래프)
    int playerIndex = enemyCount;
    for (int i = 0; i < enemyCount; i++)
    {
        *getElement(distanceMatrix, (Pos){playerIndex, i}) = max(
            abs(enemies[playerIndex].row - enemies[i].row),
            abs(enemies[playerIndex].column - enemies[i].column));

        *getElement(distanceMatrix, (Pos){i, playerIndex}) = INT_INF;
    }

    // TSP
    Matrix *matrix = newMatrix(enemyCount + 1, 1 << enemyCount);
    fillMatrix(matrix, -1);
    int minValue = INT_INF;
    for (int i = 0; i < enemyCount; i++)
    {
        int value = calc(matrix, distanceMatrix, playerIndex, i);
        if (value < minValue)
            minValue = value;
    }

    printf("%d\n", minValue);

    freeMatrix(distanceMatrix);
    freeMatrix(matrix);
}