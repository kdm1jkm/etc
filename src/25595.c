#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _pos
{
    int x, y;
} Pos;

Pos indexToPos(int index, int n)
{
    Pos pos = {index % n, index / n};
    return pos;
}

bool isCatchable(Pos pos1, Pos pos2)
{
    int deltaX = abs(pos1.x - pos2.x);
    int deltaY = abs(pos1.y - pos2.y);

    return (deltaX % 2) != (deltaY % 2);
}

int main()
{
    int n;
    scanf("%d", &n);

    int *map = malloc(sizeof(int) * n * n);
    for (int i = 0; i < n * n; i++)
        scanf("%d", map + i);

    // 신에이 노우젠
    int sn_index = -1;
    for (int i = 0; i < n * n; i++)
    {
        if (map[i] == 2)
        {
            sn_index = i;
            break;
        }
    }

    Pos sn_pos = indexToPos(sn_index, n);

    for (int i = 0; i < n * n; i++)
    {
        if (map[i] != 1)
            continue;

        Pos p = indexToPos(i, n);

        if (!isCatchable(sn_pos, p))
        {
            puts("Kiriya");
            return 0;
        }
    }

    puts("Lena");

    free(map);

    return 0;
}