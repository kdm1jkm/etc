/*
 * 2���� ���� �޸� �Ҵ�
*/

#include <stdio.h>
#include <stdlib.h>  // malloc, free �Լ��� ����ϱ� ���� stdlib.h ��������� ����
#include <string.h>  // strcpy �Լ��� ����ϱ� ���� string.h ��������� ����

int main(void) {
    char **arr2d;  // 2���� �����޸𸮸� �Ҵ���� ������
    int i;

    arr2d = (char **)malloc(3 * sizeof(char *));    // 3���� ���ڹ迭�� ����ų �� �ִ� �����͸� �����޸𸮷� �Ҵ�
    arr2d[0] = (char *)malloc(12 * sizeof(char));   // ù ��° ���ҿ� 12����Ʈ ũ���� ���ڹ迭�� �����޸𸮷� �Ҵ� (11������ ���ڿ�)
    strcpy(arr2d[0], "Programming");                // ���ڿ� ����(�� ����)
    arr2d[1] = (char *)malloc(6 * sizeof(char));    // �� ��° ���ҿ� 6����Ʈ ũ���� ���ڹ迭�� �����޸𸮷� �Ҵ� (11������ ���ڿ�)
    strcpy(arr2d[1], "Hello");                      // ���ڿ� ����(�� ����)
    arr2d[2] = (char *)malloc(7 * sizeof(char));    // �� ��° ���ҿ� 7����Ʈ ũ���� ���ڹ迭�� �����޸𸮷� �Ҵ� (11������ ���ڿ�)
    strcpy(arr2d[2], "World!");                      // ���ڿ� ����(�� ����)

    for (i = 0; i < 3; i++)
        printf("arr2d[%d]: %s\n", i, arr2d[i]);

    // �������� free!!
    free(arr2d);

    return 0;
}