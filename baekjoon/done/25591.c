#include <stdio.h>

int main()
{
    int a, b;
    scanf("%d %d", &a, &b);

    int c = a + b - 100;

    a = 100 - a;
    b = 100 - b;

    int d = a * b;

    int q = c;
    int r = d;

    q = r / 100;
    r %= 100;

    printf("%d %d %d %d %d %d\n%d %d\n", a, b, c, d, q, r, c + q, r);

    return 0;
}