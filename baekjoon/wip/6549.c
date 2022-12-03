#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int sumTree(int *tree, int index)
{
    int sum = 0;
    while (index > 0)
    {
        sum += tree[index - 1];
        index -= index & -index;
    }
    return sum;
}

void updateTree(int *tree, int value, int index, int n)
{
    while (index <= n)
    {
        tree[index - 1] += value;
        index += (index & -index);
    }
}

void calcTree(int *arr, int *tree)
{
}

int calcSize(int *arr, int n)
{
}

int main()
{
    int n = -1;
    while (true)
    {
        scanf("%d", &n);
        if (n == 0)
            break;

        int *arr = malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++)
            scanf("%d", &arr[i]);

        int size = calcSize(arr, n);

        printf("%d\n", size);
    }
}