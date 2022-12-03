#include <stdio.h>
#include <stdint.h>

int main()
{
    int count;
    scanf("%d", &count);

    int max = 1;
    int min = INT32_MAX;

    for (int i = 0; i < count; i++)
    {
        int num;
        scanf("%d", &num);
        max = max > num ? max : num;
        min = min < num ? min : num;
    }

    printf("%d", max * min);

    return 0;
}