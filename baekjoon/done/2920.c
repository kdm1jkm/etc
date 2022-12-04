#include <stdio.h>

int calc()
{
    int n;
    scanf("%d", &n);
    if (n == 1)
    {
        for (int i = 2; i <= 8; i++)
        {
            scanf("%d", &n);
            if (n != i)
                return 0;
        }
        return 1;
    }
    else if (n == 8)
    {
        for (int i = 7; i >= 1; i--)
        {
            scanf("%d", &n);
            if (n != i)
                return 0;
        }
        return 2;
    }

    return 0;
}

int main()
{
    switch (calc())
    {
    case 0:
        printf("mixed\n");
        break;

    case 1:
        printf("ascending\n");
        break;

    case 2:
        printf("descending\n");
    }
}