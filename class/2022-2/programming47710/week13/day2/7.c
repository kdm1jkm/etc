#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *fp = fopen("./proverbs1.txt", "r");
    if (fp == NULL)
    {
        printf("Failed to open the file.\n");
        exit(1);
    }

    while (1)
    {
        int c = fgetc(fp);
        if (feof(fp))
            break;
        fprintf(stdout, "%c", c);
    }
    fclose(fp);
    printf("\n");
    return 0;
}
