/*
 * �����޸� �Ҵ� + ����ȯ(type casting)
 * N���� ���Ҹ� ���� ���� �迭 ���� ����
*/

#include <stdio.h>
#include <stdlib.h>  // malloc, free �Լ��� ����ϱ� ���� stdlib.h ��������� ����


int main(void) {
    int *arr1;  // �����޸𸮸� �Ҵ���� ������
    int N;      // ����ڿ��� �Է¹��� �迭�� ũ��
    int i;
    scanf("%d", &N);
    arr1 = (int *)malloc(N * sizeof(int)); // N���� int�� ���Ҹ� ���� �迭�� �����޸𸮷� �Ҵ�

    // �迭ó�� ���
    for (i = 0; i < N; i++)
        arr1[i] = i * 10;

    // ��µ�!
    for (i = 0; i < N; i++)
        printf("arr1[%d]: %d\n", i, arr1[i]);

    // ���� ���� free!!
    free(arr1);

    return 0;
}