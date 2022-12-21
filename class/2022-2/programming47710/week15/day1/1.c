#include <stdlib.h>
int main()
{
    // 1
    int *p1;
    p1 = (int *)malloc(sizeof(int) * 10);

    // 2
    char *p2;
    p2 = (char *)calloc(10, sizeof(char));

    // 3
    char *p3;
    p3 = (char *)malloc(10 * sizeof(char));
}