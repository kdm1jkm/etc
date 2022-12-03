#include <stdio.h>
#include <stdbool.h>

bool isGroup(const char *str)
{
    bool checked[26];
    for (int i = 0; i < 26; i++)
        checked[i] = false;

    char last = ';';
    while (*str != '\0')
    {
        if (checked[*str - 'a'] && last != *str)
            return false;

        checked[*str - 'a'] = true;

        last = *str;
        str++;
    }
    return true;
}

int main()
{
    int n;
    scanf("%d", &n);

    char str[101];

    int result = 0;

    for (int i = 0; i < n; i++)
    {
        scanf("%s", str);
        if (isGroup(str))
            result++;
    }

    printf("%d\n", result);
}