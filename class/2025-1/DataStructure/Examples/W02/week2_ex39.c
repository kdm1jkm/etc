/*
 * ����ü�� �޸�
 */

#include <stdio.h>

// 2����Ʈ + 2����Ʈ + 2����Ʈ
struct type_a {
    short a_short_1;
    short a_short_2;
    short a_short_3;
};

// 2����Ʈ + 4����Ʈ
struct type_b {
    short b_short_1;
    int   b_int_1;
};

// 2����Ʈ + 8����Ʈ + 4����Ʈ
struct type_c {
    short  c_short_1;
    double c_double_1;
    int    c_int_1;
};

int main(void) {
    struct type_a a;
    struct type_b b;
    struct type_c c;

    // ��������?
    printf("Address of a.a_short_1:  %p(in decimal: %d)\n", &a.a_short_1, &a.a_short_1);
    printf("Address of a.a_short_2:  %p(in decimal: %d)\n", &a.a_short_2, &a.a_short_2);
    printf("Address of a.a_short_3:  %p(in decimal: %d)\n", &a.a_short_3, &a.a_short_3);
    printf("sizeof a: %d\n\n", sizeof(a));

    // ��������?
    printf("Address of b.b_short_1:  %p(in decimal: %d)\n", &b.b_short_1, &b.b_short_1);
    printf("Address of b.b_int_1:    %p(in decimal: %d)\n", &b.b_int_1, &b.b_int_1);
    printf("sizeof b: %d\n\n", sizeof(b));

    // ��������?
    printf("Address of c.c_short_1:  %p(in decimal: %d)\n", &c.c_short_1, &c.c_short_1);
    printf("Address of c.c_double_1: %p(in decimal: %d)\n", &c.c_double_1, &c.c_double_1);
    printf("Address of c.c_int_1:    %p(in decimal: %d)\n", &c.c_int_1, &c.c_int_1);
    printf("sizeof c: %d\n\n", sizeof(c));

    return 0;
}