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

    f = fopen("something", "wb+");

    fwrite(&score, sizeof(pscore), 1, f);
    fread(&score, sizeof(pscore), 1, f);

    fclose(f);
}