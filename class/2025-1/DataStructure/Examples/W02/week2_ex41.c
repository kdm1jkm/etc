/*
 * ����ü ������
 */

#include <stdio.h>

struct student {
    char name[20];
    int studentid;
    double grade;
};

int main(void) {
    struct student puang = {"Puang", 20210000, 4.5};

    struct student *p;

    p = &puang;
    printf("Name: %s\n", (*p).name);    // �������� ������ �켱�ϱ� ���ؼ� ��ȣ�� ���
    printf("Student ID: %d\n", (*p).studentid);
    printf("Grade: %.1f\n", (*p).grade);
    printf("Size of p: %d\n\n", sizeof(p)); // �����Ϳ� ���� ����?? �� ũ���??

    return 0;
}