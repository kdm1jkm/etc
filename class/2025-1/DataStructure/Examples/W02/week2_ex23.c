/*
 * �����޸� �Ҵ� (malloc & free) #2
 * free�� ����ϴ� ����
*/

#include <stdio.h>
#include <stdlib.h>  // malloc, free �Լ��� ����ϱ� ���� stdlib.h ��������� ����

void allocate_memory(void) {
    void *arr = malloc(10000); // 10KB ũ�� �����޸� �Ҵ�
    free(arr); // �����޸� ����(��ȯ)
}

int main(void) {
    int i = 0;
    while (1) {
        printf("%dth loop\n", ++i);
        allocate_memory(); // �ݺ��ؼ� �Լ��� ȣ��
    }

/* 4����Ʈ�� �������� �Ҵ�
   �ް�, int������ ��� */

    return 0;
}