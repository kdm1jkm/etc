/*
 * �����޸� �Ҵ� (malloc & free) #1
 * �迭(���ø޸�)�� �޸� �Ҵ�� ����
*/

#include <stdio.h>

void create_array(void) {
    char arr[10000]; // �� 10KB ũ�⸦ ������ �迭�� ����
}

int main(void) {
    int i = 0;
    while (1) {
        printf("%dth loop\n", ++i);
        create_array(); // �ݺ��ؼ� �Լ��� ȣ��
    }

    return 0;
}