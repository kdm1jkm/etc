/*
 * ����ü�� �ʿ伺
 */

#include <stdio.h>

int main(void) {
    // �л��� ������ �����ϱ� ���� ������
    char name[] = "Puang";
    int year = 2021;
    char major[] = "Software";
    char address[] = "Incheon, Korea";
    double grade_programming = 4.5;
    double grade_oss_python  = 4.0;

    // �л� �Ѹ��� �� �߰��ϱ� ���ؼ���?
    char name2[] = "Chung-Ang";
    int year2 = 1916;
    char major2[] = "Software";
    char address2[] = "Seoul, Korea";
    double grade_programming2 = 4.0;
    double grade_oss_python2  = 3.5;

    // Puang�� �ּҴ�?
    printf("Address of Puang: %s\n", address);

    // Chung-Ang�� ������?
    printf("Year of Chung-Ang: %d\n", year2);

    // Puang�� ���α׷��� ������?
    printf("Programming grade of Puang: %.1f\n", grade_programming);

    // Chung-Ang�� OSS Python ������?
    printf("OSS Python grade of Chung-Ang: %.1f\n", grade_oss_python2);
    return 0;
}