#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(char *a, char *b)
{
    int len = strlen(a) - strlen(b);
    return -(len ? len : strcmp(a, b));
}

char *getWord(char *data, int index)
{
    return data + index * 51;
}

void sort(char *data, int *indexes, int startIndex, int endIndex)
{
    if (startIndex >= endIndex)
        return;

    int pivot = indexes[(startIndex + endIndex) / 2];
    int left = startIndex;
    int right = endIndex;

    while (1)
    {
        while (compare(getWord(data, indexes[startIndex]), getWord(data, pivot)) > 0)
            startIndex++;
        while (compare(getWord(data, indexes[endIndex]), getWord(data, pivot)) < 0)
            endIndex--;

        if (startIndex > endIndex)
            break;

        int temp = indexes[startIndex];
        indexes[startIndex] = indexes[endIndex];
        indexes[endIndex] = temp;
        startIndex++;
        endIndex--;
    }

    sort(data, indexes, left, endIndex);
    sort(data, indexes, startIndex, right);
}

int main()
{
    int count;
    scanf("%d", &count);

    char *strings;
    int *indexes;
    strings = (char *)malloc(count * sizeof(char) * 51);
    indexes = (int *)malloc(count * sizeof(int));

    for (int i = 0; i < count; i++)
    {
        scanf("%s", getWord(strings, i));
        indexes[i] = i;
    }

    sort(strings, indexes, 0, count - 1);

    int temp = 0;
    printf("%s\n", getWord(strings, indexes[temp]));
    for (int i = 0; i < count; i++)
    {
        if (strncmp(getWord(strings, indexes[temp]), getWord(strings, indexes[i]), 51) != 0)
        {
            printf("%s\n", getWord(strings, indexes[i]));
            temp = i;
        }
    }

    free(strings);
    free(indexes);
}