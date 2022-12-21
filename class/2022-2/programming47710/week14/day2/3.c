#include <stdio.h>

#define SUM(a, b) ((a) + (b))
#define PRODUCT(x, y) ((x) * (y))

int main()
{
    printf("%d\n", SUM(3 + 4, 4 * 2));
    printf("%d\n", PRODUCT(3 + 4, 4 * 2));
    printf("%d\n", PRODUCT(7, 8));

    return 0;
}