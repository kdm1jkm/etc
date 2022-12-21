#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

typedef struct
{
    char name[100];
    int point;
} pscore;

int main()
{
    pscore score;
    char line[80];
    FILE *f;
    int ch;

    if ((f = fopen("d:\\proverbs1.txt", "r")) == NULL)
    {
        printf("Failed to open the file.\n");
        exit(1);
    }

    ch = fgetc(f);
    fgets(line, 80, stdin);
}