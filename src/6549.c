#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

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

        int *tree =
    }
}