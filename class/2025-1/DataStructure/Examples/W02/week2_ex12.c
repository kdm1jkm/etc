/*
 * �������� �迭 (VLA: Variable Length Array)
 */

#include <stdio.h>

int main(void) {
    // ������ ���� �Ҵ��ϰ� �迭�� ũ��� ����� �� �ִ�.
    int size = 10;
    int array1[size];
    // �迭�� ���̴� �迭�� �� ����Ʈũ�� / �迭�� �� ����� ����Ʈũ��
    printf("size of array1: %ld\n", sizeof(array1) / sizeof(int));

    // ���� ����ڷκ��� �Է��� �޾Ƽ� �迭�� ũ�⸦ ������ �� �ִ�.
    int N;
    printf("input the number of elements: ");
    scanf("%d", &N);
    int array2[N];
    printf("size of array2: %ld\n", sizeof(array2) / sizeof(int));

    return 0;
}