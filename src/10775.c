#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int index, value;
} Pair;

int compare(const void *a, const void *b)
{
    int result = ((Pair *)a)->value - ((Pair *)b)->value;
    if (result != 0)
        return result;
    return (((Pair *)a)->index - ((Pair *)b)->index);
}

int main()
{
    int g, p;
    scanf("%d", &g);
    scanf("%d", &p);

    Pair *arr = (Pair *)malloc(sizeof(Pair) * p);
    for (int i = 0; i < p; i++)
    {
        scanf("%d", &arr[i].a);
        arr[i].b = i + 1;
    }

    qsort(arr, p, sizeof(Pair), compare);

    int count = p;
    int capacity = 0;

    int prev = 0;
    for (int i = 0; i < p; i++)
    {
        capacity += arr[i].a - prev;

        if (capacity <= 0)
        {
            count = arr[i].b;
            break;
        }
        else
            capacity -= 1;

        prev = arr[i].a;
    }

    printf("%d\n", count);
}