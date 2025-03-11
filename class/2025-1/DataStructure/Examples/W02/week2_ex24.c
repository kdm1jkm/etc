/*
 * �����޸� �Ҵ� + ����ȯ(type casting)
*/

#include <stdio.h>
#include <stdlib.h>  // malloc, free �Լ��� ����ϱ� ���� stdlib.h ��������� ����


int main(void) {
    // 4����Ʈ ũ�� �����޸� �Ҵ� �� int �����ͷ� ����
    int *p = (int *)malloc(4);
    // -> p�� ����Ű�� ������ ���� int������ �����͸� �ٷ�ž�!

    // char �ڷ����� ũ��(1����Ʈ) �����޸� �Ҵ� �� char �����ͷ� ����
    char *q = (char *)malloc(sizeof(char));
    // -> q�� ����Ű�� ������ ���� char������ �����͸� �ٷ�ž�!

    *p = 10;
    *q = 'A';

    printf("p: %p, *p: %d\n", p, *p);
    printf("q: %p, *q: %c\n", q, *q);

    // ���� ���� free!!
    free(p);
    free(q);

    return 0;
}