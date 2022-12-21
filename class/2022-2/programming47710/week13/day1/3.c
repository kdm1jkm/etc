#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *fp, *fp2;
    char fn[40], fn2[40];
    char txt[512];

    if (argc != 3)
    {
        printf("Usage: mycopy srcfile dstfile\n");
        exit(1);
    }

    strcpy(fn, argv[1]);
    strcpy(fn2, argv[2]);

    fp = fopen(fn, "r");
    fp2 = fopen(fn2, "w");

    if (fp == NULL || fp2 == NULL)
    {
        printf("Cannot open file.\n");
        exit(1);
    }

    int read;
    while ((read = fread(txt, sizeof(char), 512, fp)) > 0)
    {
        fwrite(txt, sizeof(char), read, fp2);
        fwrite(txt, sizeof(char), read, stdout);
    }

    fclose(fp);
    fclose(fp2);

    return 0;
}