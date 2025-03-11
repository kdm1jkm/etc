/*
 * typedef
 */

#include <stdio.h>

struct student {
    char *name;
    int studentid;
    double grade;
};

// struct student Ÿ���� student�� ������
typedef struct student student;
// unsigned long long int Ÿ���� ull�� ������
typedef unsigned long long int ull;

int main(void) {
    // Ÿ���� ���Ӱ� �������ص� ���� Ÿ���� ��� ����� �� �ִ�. (���� ������ ���� ���� ��)
    struct student chung_ang = {"Chung-Ang", 1916, 4.0};
    student puang = {"Puang", 20210000, 4.5};

    printf("size of chung_ang: %d\n", sizeof(chung_ang));
    printf("size of puang: %d\n", sizeof(puang));

    // �⺻ �ڷ����� �����ǰ� �����ϴ�.
    ull a = 1234;
    unsigned long long int b = 1234;

    printf("size of a: %d\n", sizeof(a));
    printf("size of b: %d\n", sizeof(b));

    return 0;
}