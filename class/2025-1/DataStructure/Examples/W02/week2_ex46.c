/*
 * typedef
 */

#include <stdio.h>

// ����ü�� �����ϸ鼭 �ٷ� typedef Ű���带 ����� �� �ִ�.
typedef struct _student_t {
    char *name;
    int studentid;
    double grade;
} student_t;

int main(void) {
    // Ÿ���� ���Ӱ� �������ص� ���� Ÿ���� ��� ����� �� �ִ�. (���� ������ ���� ���� ��)
    struct _student_t chung_ang = {"Chung-Ang", 1916, 4.0};
    student_t puang = {"Puang", 20210000, 4.5};

    printf("size of chung_ang: %d\n", sizeof(chung_ang));
    printf("size of puang: %d\n", sizeof(puang));

    return 0;
}