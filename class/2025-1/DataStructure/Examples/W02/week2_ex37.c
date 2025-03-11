/*
 * ����ü�� ���ǿ� �ʱ�ȭ
 */

#include <stdio.h>

struct student {
    char name[20];
    int year;
    char major[20];
    char address[50];
    double grade_programming;
    double grade_oss_python;
};

int main(void) {
    // ����ü ������ �ʱ�ȭ �� ������ ����� ������ �°� ���� �־��־�� �Ѵ�.
    struct student puang = {"Puang", 2021, "Software", "Incheon, Korea", 4.5, 4.0};

    // �л� �Ѹ��� �� �߰��ϱ� ���ؼ���?
    struct student chung_ang = {
        .year = 1916,           // ����� �̸��� ��������� ������ ���� �ִ�.
        .name = "Chung-Ang",    // �� ��� ������ �ٲ� ����� ����.
        .major = "Software",    // ���� �ʱ�ȭ���� ���� ����� 0���� �ʱ�ȭ�ȴ�.
        .address = "Seoul, Korea",
        .grade_oss_python = 3.5,
        .grade_programming = 4.0
    };

    // Puang�� �ּҴ�?
    printf("Address of Puang: %s\n", puang.address);

    // Chung-Ang�� ������?
    printf("Year of Chung-Ang: %d\n", chung_ang.year);

    // Puang�� ���α׷��� ������?
    printf("Programming grade of Puang: %.1f\n", puang.grade_programming);

    // Chung-Ang�� OSS Python ������?
    printf("OSS Python grade of Chung-Ang: %.1f\n", chung_ang.grade_oss_python);
    return 0;
}