/*
 * C��� ������ ���� ���� ���� ��ġ ����
 */

#include <stdio.h>

/* C90���� ������ // ��Ÿ���� �� �� �ּ��� ������ ���� �ʴ´�...  */
int main() {
    printf("Do something...\n");    /* ��� �۾��� �����ϰ�... */
    int var1 = 20;                  /* ������ �����ϸ�? */
    printf("Does it work?\n");

    /* �ش� C��� ǥ���� �ؼ��ϴ��� ������ Ȯ���ϱ� ���ؼ��� -pedantic-errors �ɼ��� ����Ѵ�. */
    /* ex) gcc -o run.exe source.c -std=c89 -pedantic-errors*/
    /*     --> source.c ������ run.exe ���Ϸ� �������ϸ�, c89 ǥ������ �������ϰ� ������ ������ Ȯ�� */
    return 0;
}