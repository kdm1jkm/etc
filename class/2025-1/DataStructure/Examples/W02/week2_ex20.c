/*
 * �����޸� �Ҵ� (malloc)
*/

#include <stdio.h>
#include <stdlib.h> // �����޸� ������ ���� �Լ��� stdlib.h�� ����Ǿ� �ִ�.

int global_var1;    // ��������

int main(void) {
    int var1, var2, var3;   // ��������
    void *p1;
    p1 = malloc(10000000);    // 10MB�� ũ�⸦ �Ҵ��� �� �ִ°�?
    void *p2;
    p2 = malloc(10000000);    // p2�� �ٽ� malloc�� ���� �����޸� �Ҵ�
    
    printf("%p:Code segment (main function)\n", main);
    printf("%p:Data segment\n", &global_var1);
    printf("%p:Stack segment (var1)\n", &var1);
    printf("%p:Stack segment (var2)\n", &var2);
    printf("%p:Stack segment (var3)\n", &var3);

    if (p1 == NULL) {    // malloc �Լ��� �Ҵ翡 �����ϸ� NULL�� ��ȯ
        printf("Failed to allocate memory (p1)!\n");
    } else {            // NULL�� �ƴϸ� �Ҵ��� ���� ��
        printf("Success to allocate 10MB memory (p2)!\n");
        printf("%p:Stack segment (p1)\n", &p1);
        printf("%p:Heap segment (allocated memory (in p1))\n", p1);
    }

    if (p2 == NULL) {    // malloc �Լ��� �Ҵ翡 �����ϸ� NULL�� ��ȯ
        printf("Failed to allocate memory (p2)!\n");
    } else {            // NULL�� �ƴϸ� �Ҵ��� ���� ��
        printf("Success to allocate 10MB memory (p2)!\n");
        printf("%p:Stack segment (p2)\n", &p2);
        printf("%p:Heap segment (allocated memory (in p2))\n", p2);
    }

    return 0;
}