/*
 * �޸� ���� �Լ� (memset)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int i;
    int *p = (int *)malloc(5 * sizeof(int));

    // �ʱ�ȭ�� ���� �ʰ� ����ϸ� �����Ⱚ(dummy value)�� ��µȴ�.
    for (i = 0; i < 5; i++) printf("p[%d]:0x%02X\n", i, p[i]);

    // memset �Լ��� ����Ͽ� 0���� �ʱ�ȭ
    memset(p, 0, 5 * sizeof(int));  // 5 * sizeof(int)��ŭ�� �޸𸮸� 0���� �ʱ�ȭ
    printf("memset to 0\n");
    for (i = 0; i < 5; i++) printf("p[%d]:0x%02X\n", i, p[i]);

    // memset �Լ��� ����Ͽ� 0x12�� �ʱ�ȭ
    memset(p, 0x12, 5 * sizeof(int));
    printf("memset to 0x12\n");
    for (i = 0; i < 5; i++) printf("p[%d]:0x%02X\n", i, p[i]);

    // ���� ���� free!!
    free(p);

    return 0;
}
