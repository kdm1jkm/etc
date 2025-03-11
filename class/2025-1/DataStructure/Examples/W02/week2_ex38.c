/*
 * �迭 vs ����ü
 */

#include <stdio.h>

// ����ü�� ����� ���� �ٸ� �ڷ����� ���� �� �ִ�.
struct student {
    char name[6];
    int studentid;
    double grade;
};

int main(void) {
    // �迭�� ����ü ��� �߰�ȣ�� �ʱ�ȭ
    struct student puang = {"Puang", 20210000, 4.5};    // ����ü�� ����� ���� �ٸ� �ڷ����� ���� �� �ִ�.
    double grades[4] = {4.5, 4.0, 3.5, 4.0};            // �迭�� ���Ҵ� ��� ������ �ڷ������� �����ȴ�.
    double grades2[10] = {0};   // �迭�� ������ ������ ũ�⸦ ������ �� ������, ����ü�� �ѹ� �����ϸ� ũ�⸦ �ٲ� �� ����.
    
    int i;
    // �迭�� ���ҵ��� ���� ���ӵ� �޸𸮿� ����ȴ�.
    for (i = 0; i < 4; i++) {
        printf("Address of grades[%d]:       %p(in decimal: %d)\n", i, &grades[i], &grades[i]);
    }
    printf("sizeof array: %d\n", sizeof(grades));

    // ����ü�� ������� ���� ���ӵ� �޸𸮿� ������� ���� �� �ִ�.
    printf("\n\n");
    printf("Address of puang.name:      %p(in decimal: %d)\n", puang.name, puang.name);
    printf("Address of puang.studentid: %p(in decimal: %d)\n", &puang.studentid, &puang.studentid);
    printf("Address of puang.grade:     %p(in decimal: %d)\n", &puang.grade, &puang.grade);
    printf("sizeof struct: %d\n", sizeof(puang));

    return 0;
}