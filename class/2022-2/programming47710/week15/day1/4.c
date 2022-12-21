#include <stdlib.h>

int main()
{
    int *p, *ptr;

    p = (int *)calloc(3, sizeof(int));
    free(p);

    ptr = (int *)realloc(NULL, 4 * sizeof(int));
    free(ptr);
    p = (int *)realloc(NULL, 4 * sizeof(int));

    ptr = (int *)realloc(p, 4 * sizeof(int));

    // p is dangling pointer!
    p = (int *)realloc(p, 4 * sizeof(int));
}