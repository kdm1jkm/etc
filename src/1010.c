#include <stdio.h>

int min(int a, int b)
{
    return a < b ? a : b;
}

int main()
{
    int count;
    scanf("%d", &count);
    for (int loop = 0; loop < count; loop++)
    {
        int n, m;
        scanf("%d %d", &n, &m);

        unsigned long long int result = 1;

        for (int i = 0; i < min(n, m - n); i++)
        {
            result *= (m - i);
            result /= (i + 1);
        }

        printf("%lld\n", result);
    }
}