/*
 * �޸� ���� �Լ� (calloc)
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int i;
    int *malloc_p = (int *)malloc(5 * sizeof(int)); // int�� �����͸� 5�� ������ �� �ִ� ���� �޸𸮸� �Ҵ�޾� p�� ����
    int *calloc_p = (int *)calloc(5,  sizeof(int)); // int�� �����͸� 5�� ������ �� �ִ� ���� �޸𸮸� �Ҵ�޾� p�� ����

    // malloc�� �Ҵ���� �޸��� ���� �ʱ�ȭ���� �ʴ´�.
    for (i = 0; i < 5; i++)
        printf("malloc_p[%d]: %d\n", i, malloc_p[i]);

    // calloc�� �Ҵ���� �޸��� ���� 0���� �ʱ�ȭ�ȴ�.
    for (i = 0; i < 5; i++)
        printf("calloc_p[%d]: %d\n", i, calloc_p[i]);

    // �������� free!!
    free(malloc_p);
    free(calloc_p);

    return 0;
}
