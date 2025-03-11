/*
 * ����ü �������� ���� ������
 */

#include <stdio.h>

struct student {
    char *name;
    int studentid;
    double grade;
};

int main(void) {
    struct student puang = {"Puang", 20210000, 4.5};

    struct student *p;

    p = &puang;
    printf("===== Access by pointer, and then access member =====\n");
    printf("Name: %s\n", (*p).name);    // �������� ������ �켱�ϱ� ���ؼ� ��ȣ�� ���
    printf("Student ID: %d\n", (*p).studentid);
    printf("Grade: %.1f\n", (*p).grade);

    // ����������(*) �� �������(.)�� �� ���� ������ ���ִ�. �������� ����� ���� (->)
    printf("===== Access member of pointer directly =====\n");
    printf("Name: %s\n", p->name);
    printf("Student ID: %d\n", p->studentid);
    printf("Grade: %.1f\n", p->grade);


    return 0;
}