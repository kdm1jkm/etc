/*
 * ���ø޸�
*/

#include <stdio.h>

// �Լ���
void myfunc1(int p1, short p2, double p3) {
    printf("--- [myfunc1] ---\n");
    printf("  p1: %p\n", &p1);
    printf("  p2: %p\n", &p2);
    printf("  p3: %p\n", &p3);
}
void myfunc2(int *p1, short *p2, double *p3) {
    int var1, var2, var3;
    printf("--- [myfunc2] ---\n");
    printf("  p1: %p\n", &p1);
    printf("  p2: %p\n", &p2);
    printf("  p3: %p\n", &p3);
    printf("var1: %p\n", &var1);
    printf("var2: %p\n", &var2);
    printf("var3: %p\n", &var3);
    myfunc1(*p1, *p2, *p3);
}

int main(void) {
    // ����������
    int var1;
    short var2;
    double var3;

    // ��������(�Լ� ���ο� �����ϴ� ����)�� �޸𸮴� ���ø޸𸮿� �Ҵ�
    // ����� ������� ���� �ּҺ��� ���� �ּҷ� �Ҵ�
    printf("====== memory of local variables ======\n");
    printf("var1: %p\n", &var1);
    printf("var2: %p\n", &var2);
    printf("var3: %p\n", &var3);

    // myfunc1�� ȣ���ϸ�?
    printf("Call myfunc1 in main\n");
    myfunc1(var1, var2, var3);
    /* main�Լ��� stack�޸𸮿� �̾ myfunc1�� ���õ� �޸𸮰� ����Ǿ���. */


    // myfunc2�� ȣ���ϸ�?
    printf("Call myfunc2 in main\n");
    myfunc2(&var1, &var2, &var3);
    /* myfunc1�� ����ߴ� �޸𸮸� �ٽþ��� �ִ�. �׸���,
       main�Լ��� stack�޸𸮿� �̾ myfunc2�� ���õ� �޸𸮰� ����� ���� 
       myfunc2�Լ��� stack�޸𸮿� �̾ myfunc1�� ȣ��Ǹ� ���õ� �޸𸮰� ����ȴ�.*/

    return 0;
}