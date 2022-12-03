#include <stdio.h>
#include <string.h>

void reverse(char *word, int begin, int end)
{
    while (begin < end)
    {
        char temp = word[begin];
        word[begin] = word[end];
        word[end] = temp;

        begin++;
        end--;
    }
}

void reverseThree(char *word, int *indexes, int indexCount)
{
    reverse(word, 0, indexes[0]);
    for (int i = 1; i < indexCount; i++)
    {
        reverse(word, indexes[i - 1] + 1, indexes[i]);
    }
}

int main()
{
    char word[51];
    scanf("%s", word);

    int len = strlen(word);

    int indexes[3] = {0, 1, len - 1};

    char result[51];
    strncpy(result, word, 51);
    reverseThree(result, indexes, 3);

    for (indexes[0] = 0; indexes[0] < len - 2; indexes[0]++)
    {
        for (indexes[1] = indexes[0] + 1; indexes[1] < len - 1; indexes[1]++)
        {
            reverseThree(word, indexes, 3);
            if (strcmp(result, word) > 0)
                strcpy(result, word);
            reverseThree(word, indexes, 3);
        }
    }

    printf("%s\n", result);
}