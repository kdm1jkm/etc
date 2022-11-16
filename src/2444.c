#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);

    for (int row = 0; row < n; row++)
    {
        for (int column = 0; column < n + row; column++)
        {
            if ((n - 1 - row) <= column && column <= (n - 1 + row))
                putchar('*');
            else
                putchar(' ');
        }
        putchar('\n');
    }
    for (int row = 0; row < n - 1; row++)
    {
        for (int column = 0; column < 2 * n - 2 - row; column++)
        {
            if (row + 1 <= column && column <= (2 * n - 3 - row))
                putchar('*');
            else
                putchar(' ');
        }
        putchar('\n');
    }
}