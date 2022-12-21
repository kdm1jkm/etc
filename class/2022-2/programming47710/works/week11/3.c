#include <stdio.h>

int main()
{
    int m[3][2] = {1, 2, 3, 4, 5, 6};
    printf("%d\n", **m);
    printf("%d\n", *m[1]);
}