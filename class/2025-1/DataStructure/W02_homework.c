#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _student_t
{
    char name[10];
    double kor_score;
    double eng_score;
    double math_score;
} student_t;

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("Usage: %s [fpath] [subject]", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("Cannot open the file %s\n", argv[1]);
        return 2;
    }

    const char *SUBJECTS[] = {"kor", "eng", "math", "total"};

    for (int i = 0; i < 4; i++)
    {
        if (strcmp(argv[2], SUBJECTS[i]) == 0)
        {
            break;
        }
        else if (i == 3)
        {
            printf("Invalid subject %s\n", argv[2]);
            return 3;
        }
    }

    int INIT_SIZE = 10;

    int students_capacity = INIT_SIZE;
    student_t *students = (student_t *)malloc(sizeof(student_t) * students_capacity);
    int students_count = 0;

    int highest_index = 0;
    double highest_score = 0.0;

    char buffer[256];
    while (fgets(buffer, 256, fp) != NULL)
    {
        if (students_count >= students_capacity)
        {
            students_capacity *= 2;
            students = (student_t *)realloc(students, sizeof(student_t) * students_capacity);
        }

        student_t *student = &students[students_count];
        sscanf(buffer, "%s %lf %lf %lf", student->name, &student->kor_score, &student->eng_score, &student->math_score);

        double current_score = 0.0;

        if (strcmp(argv[2], "kor") == 0)
        {
            current_score = student->kor_score;
        }
        else if (strcmp(argv[2], "eng") == 0)
        {
            current_score = student->eng_score;
        }
        else if (strcmp(argv[2], "math") == 0)
        {
            current_score = student->math_score;
        }
        else if (strcmp(argv[2], "total") == 0)
        {
            current_score = student->kor_score + student->eng_score + student->math_score;
        }

        if (current_score > highest_score)
        {
            highest_score = current_score;
            highest_index = students_count - 1;
        }

        students_count++;
    }

    printf("The student who has the highest %s score in the file %s is %s(%.2lf)\n", argv[2], argv[0], students[highest_index].name, highest_score);
    return 0;
}