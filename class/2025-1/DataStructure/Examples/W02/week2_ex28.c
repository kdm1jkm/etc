/*
 * 2���� ���� �޸� �Ҵ� ����
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

    /* �������� �޸𸮸� �Ҵ� ���� �� add2d���� �ƴϴ�! */
    // ������ ���ҵ� �����Ҵ��� �޾�����, ����Ű�� �޸𸮰� �ٸ���.
    printf("arr2d: %p\n", arr2d);
    printf("arr2d[0]: %p\n", arr2d[0]);
    printf("arr2d[1]: %p\n", arr2d[1]);
    printf("arr2d[2]: %p\n", arr2d[2]);
    
    // ���� free�� ���� �޸𸮸� ������ ������ ������ ���ҿ� ���ؼ��� ������ ���־�� �Ѵ�.
    free(arr2d);
    free(arr2d[0]);
    free(arr2d[1]);
    free(arr2d[2]);

    return 0;
}