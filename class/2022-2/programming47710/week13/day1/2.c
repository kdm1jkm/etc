#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *f;
    fopen_s(&f, "d:\\proverbs1.txt", "r");
    if (f == NULL)
    {
        printf("Failed to open the file.\n");
        exit(1);
    }
    fputs("\nThis text will be appended.", f);
    fclose(f);
    return 0;
}