#include <stdio.h>

#define STR_LEN 50

int main()
{
    int count;
    scanf("%d", &count);

    char string[STR_LEN + 1];
    scanf("%s", string);
    for (int i = 0; i < count - 1; i++)
    {
        char newString[STR_LEN + 1];
        scanf("%s", newString);

        for (int j = 0; j < STR_LEN; j++)
        {
            if (string[j] == '\0')
                break;

            if (string[j] == '?')
                continue;

            if (string[j] != newString[j])
                string[j] = '?';
        }
    }

    printf("%s", string);

    return 0;
}