#include <stdio.h>

int find(int num)
{
    for (int n = 2;; n += 2)
    {
        int min = n * (n + 1) / 2;
        int max = (n + 1) * (n + 2) / 2;

        if (min > num)
            break;

        if (num <= max)
            return max - num;
    }
    return 0;
}

int main()
{
    int num;
    scanf("%d", &num);

    printf("%d\n", find(num));
}