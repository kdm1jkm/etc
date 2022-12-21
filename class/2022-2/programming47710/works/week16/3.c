#include <stdio.h>

int main()
{
    int x;
    int const *p1 = &x;
    *p1 = 5;
    const int *p2 = &x;
    *p2 = 6;
    int *const p3 = &x;
    *p3 = 7;
    printf("%d\n", x);
}