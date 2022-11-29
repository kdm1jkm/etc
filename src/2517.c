#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct
{
    int index, value;
} Pair;

int compareByValue(const void *p1, const void *p2)
{
    Pair *pair1 = (Pair *)p1;
    Pair *pair2 = (Pair *)p2;
    return pair1->value - pair2->value;
}

int compareByIndex(const void *p1, const void *p2)
{
    Pair *pair1 = (Pair *)p1;
    Pair *pair2 = (Pair *)p2;
    return pair1->index - pair2->index;
}

int sum(int *tree, int i)
{
    int sum = 0;
    while (i > 0)
    {
        sum += tree[i - 1];
        i -= (i & -i);
    }
    return sum;
}

void update(int *tree, int value, int i, int n)
{
    while (i <= n)
    {
        tree[i - 1] += value;
        i += (i & -i);
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    Pair *abilities = (Pair *)malloc(sizeof(Pair) * n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &abilities[i].value);
        abilities[i].index = i + 1;
    }

    qsort(abilities, n, sizeof(Pair), compareByValue);
    for (int i = 0; i < n; i++)
        abilities[i].value = i + 1;
    qsort(abilities, n, sizeof(Pair), compareByIndex);

    // puts("-------");
    // for (int i = 0; i < n; i++)
    // {
    //     printf("%d %d\n", abilities[i].index, abilities[i].value);
    // }
    // puts("-------");

    int *tree = (int *)malloc(sizeof(int) * n);
    memset(tree, 0, sizeof(int) * n);

    for (int i = 0; i < n; i++)
    {
        printf("%d\n", (i + 1) - sum(tree, abilities[i].value - 1));
        update(tree, 1, abilities[i].value, n);
    }

    free(abilities);
    free(tree);
}

/*

1. Tree 부분합 사용하기
2. --> 이건 구하는 거도 빨리 할 수 있는데, (부분 전체에 더하는 것도 빨리 할 수 있음.) -> 이걸 이해를 못했음.

*/