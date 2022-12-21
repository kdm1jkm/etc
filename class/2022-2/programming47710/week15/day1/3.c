#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *ary = NULL;
    int i = 0;
    if ((ary = (int *)malloc(3 * sizeof(int))) == NULL)
    {
        printf("Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < 3; i++)
        printf("ary[%d] = %d\n", i, *(ary + i));
    free(ary);
    return 0;
}