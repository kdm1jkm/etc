/*
 * �޸� ���� ��ġ
*/

#include <stdio.h>

int main(void) {
    char var1[10000000];    // 10MB�� ũ�⸦ �Ҵ��� �� �ִ°�?
    printf("Success to allocate %ld-bytes memory!\n", sizeof(var1));

    /* powershell���� gcc ������ �ÿ� ���ø޸𸮸� �����ϱ� ���ؼ���
       "-Wl,--stack,[size]" �ɼ��� �߰��Ѵ�.
       ex) gcc -o run.exe source.c "-Wl,--stack,100000000"
           -> source.c ������ run.exe�� �������ϸ�, ���ø޸𸮸� �� 100MB�� ���� */

    return 0;
}