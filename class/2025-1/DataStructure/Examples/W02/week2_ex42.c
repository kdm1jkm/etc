/*
 * ����ü ������
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

    // puang��������, name�� ù ���ڿ� �����ϴ� �����?
    printf("The first letter of name of puang: %c\n", puang.name[0]);
    // 1�����迭 <-> �������� ���踦 �̿��Ͽ� name�� ù ���ڿ� �����ϴ� �����?
    printf("The first letter of name of puang: %c\n", *puang.name);

    // ����ü �����Ϳ���, name�� ù ���ڿ� �����ϴ� �����?
    printf("The first letter of name of puang: %c\n", (*p).name[0]);
    // 1�����迭 <-> �������� ���踦 �̿��Ͽ� name�� ù ���ڿ� �����ϴ� �����?
    printf("The first letter of name of puang: %c\n", *(*p).name);

    // �������(.) <-> �������ּ�����(*)�� ������ �ִ�. ���� ��������� �� ���� �켱������ ������.
    // ���� *p.name��? *(p.name)�� ����.



    return 0;
}