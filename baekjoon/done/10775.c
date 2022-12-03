#include <stdio.h>
#include <stdlib.h>

int getRoot(int *arr, int num)
{
    if (arr[num] == num)
        return num;

    return arr[num] = getRoot(arr, arr[num]);
}

void merge(int *arr, int num1, int num2)
{
    arr[getRoot(arr, num2)] = getRoot(arr, num1);
}

int main()
{
    int g, p;
    scanf("%d", &g);
    scanf("%d", &p);

    int *arr = (int *)malloc(sizeof(int) * p);
    for (int i = 0; i < p; i++)
        scanf("%d", arr + i);

    int *arr2 = (int *)malloc(sizeof(int) * (g + 1));
    for (int i = 0; i < g + 1; i++)
        arr2[i] = i;

    int count = 0;

    for (int i = 0; i < p; i++)
    {
        int root = getRoot(arr2, arr[i]);
        if (root == 0)
            break;

        count++;
        merge(arr2, root - 1, root);
    }

    printf("%d\n", count);

    free(arr);
    free(arr2);
}

/*

Union Find!!!!!!!!!!!!!!

*/