#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    FILE *fp = NULL;
    char buffer[500];
    fp = fopen("proverbs1.txt", "r");
    int line_number = 1;
    while (!feof(fp))
    {
        fgets(buffer, 500, fp);
        printf("%d: %s", line_number++, buffer);
    }

    fclose(fp);
    return 0;
}