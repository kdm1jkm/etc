#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int minIndex(long *arr, int index1, int index2)
{
    if (index1 == -1)
        return index2;
    else if (index2 == -1)
        return index1;
    else
        return arr[index1] <= arr[index2] ? index1 : index2;
}

void initTree(int *tree, long *arr, int startIndex, int endIndex, int treeIndex)
{
    if (startIndex == endIndex)
        tree[treeIndex] = startIndex;
    else
    {
        int mid = (startIndex + endIndex) / 2;
        initTree(tree, arr, startIndex, mid, treeIndex * 2);
        initTree(tree, arr, mid + 1, endIndex, treeIndex * 2 + 1);
        tree[treeIndex] = minIndex(
            arr,
            tree[treeIndex * 2],
            tree[treeIndex * 2 + 1]);
    }
}

int *newTree(long *arr, int n)
{
    int *tree = (int *)malloc(sizeof(int) * n * 4);
    initTree(tree, arr, 0, n - 1, 1);
    return tree;
}

long _queryTree(int *tree, long *arr, int targetStart, int targetEnd, int currentStart, int currentEnd, int treeIndex)
{
    if (currentEnd < targetStart || targetEnd < currentStart)
        return -1;

    if (targetStart <= currentStart && currentEnd <= targetEnd)
        return tree[treeIndex];

    int mid = (currentStart + currentEnd) / 2;

    return minIndex(
        arr,
        _queryTree(tree, arr, targetStart, targetEnd, currentStart, mid, treeIndex * 2),
        _queryTree(tree, arr, targetStart, targetEnd, mid + 1, currentEnd, treeIndex * 2 + 1));
}

long queryTree(int *tree, long *arr, int n, int start, int end)
{
    return _queryTree(tree, arr, start, end, 0, n - 1, 1);
}

long _calcSize(long *arr, int *tree, int n, int startIndex, int endIndex)
{
    if (startIndex > endIndex)
        return -1;
    int currentMinIndex = queryTree(tree, arr, n, startIndex, endIndex);

    long result = arr[currentMinIndex] * (endIndex - startIndex + 1);

    long front = _calcSize(arr, tree, n, startIndex, currentMinIndex - 1);
    long back = _calcSize(arr, tree, n, currentMinIndex + 1, endIndex);

    if (front > result)
        result = front;
    if (back > result)
        result = back;

    return result;
}

long calcSize(long *arr, int n)
{
    int *tree = newTree(arr, n);
    long result = _calcSize(arr, tree, n, 0, n - 1);
    free(tree);
    return result;
}

int main()
{
    int n = -1;
    while (true)
    {
        scanf("%d", &n);
        if (n == 0)
            break;

        long *arr = (long *)malloc(sizeof(long) * n);

        for (int i = 0; i < n; i++)
            scanf("%ld", &arr[i]);

        printf("%ld\n", calcSize(arr, n));
        free(arr);
    }
}