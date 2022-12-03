#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int x, y;
} Vec2i;

int compare(const void *a, const void *b)
{
    Vec2i *vecA, *vecB;
    vecA = (Vec2i *)a;
    vecB = (Vec2i *)b;

    int y = vecA->y - vecB->y;
    if (y != 0)
        return y;

    return vecA->x - vecB->x;
}

int main()
{
    int n;
    scanf("%d", &n);

    Vec2i *vecs = (Vec2i *)malloc(sizeof(Vec2i) * n);

    for (int i = 0; i < n; i++)
        scanf("%d %d", &vecs[i].x, &vecs[i].y);

    qsort(vecs, n, sizeof(Vec2i), compare);

    for (int i = 0; i < n; i++)
        printf("%d %d\n", vecs[i].x, vecs[i].y);
}
