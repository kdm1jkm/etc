/*
 * ����ü + �����޸� �Ҵ�
 */

#include <stdio.h>
#include <stdlib.h>

struct student {
    char *name;
    int studentid;
    double grade;
};

int main(void) {
    struct student *students;
    int N;
    printf("input the number of students: ");
    scanf("%d", &N);
    students = (struct student *)malloc(sizeof(struct student) * N);

    // do something....

    // ���� ���� free!!
    free(students);

    return 0;
}