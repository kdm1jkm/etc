/*
 * C��� ������ ���� for loop�� �ʱ�� ���� ����
 */

#include <stdio.h>

/* C90���� ������ // ��Ÿ���� �� �� �ּ��� ������ ���� �ʴ´�...  */
int main() {
    /* for loop�� �ʱ�Ŀ��� ������ �����ϸ�? */
    for (int i = 0; i < 10; i++) {
        printf("i: %d\n", i);
    }

    /* �ش� C��� ǥ���� �ؼ��ϴ��� ������ Ȯ���ϱ� ���ؼ��� -pedantic-errors �ɼ��� ����Ѵ�. */
    /* ex) gcc -o run.exe source.c -std=c89 -pedantic-errors*/
    /*     --> source.c ������ run.exe ���Ϸ� �������ϸ�, c89 ǥ������ �������ϰ� ������ ������ Ȯ�� */
    return 0;
}