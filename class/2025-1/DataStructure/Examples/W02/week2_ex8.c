/*
 * ������ �迭�� Ȱ��
 */


#include <stdio.h>

int main(void) {
    int i;
    // �迭 ����
    int arr1[3] = { 0x30, 0x44, 0x67 };
    int arr2[3] = { 0x87, 0x43 };

    // �迭�� �̸��� ���� ������ �ּ�, ���� ������ ������ �Ҵ� ����
    int *p1 = arr1;
    int *p2 = arr2;

    // �����͹迭�� ������ �������� �迭
    int *p_arr[2] = { p1, p2 };

    // p_arr[0]��? p1�� �� == arr1�� �����ּ�
    printf("p_arr[0]:%p, p1:%p, arr1:%p\n", p_arr[0], p1, arr1);

    // p_arr[0][i]��? p1�� ������ �ּҿ��� i��° ������ �� == arr1[i]
    for (i = 0; i < 3; i++)
        printf("p_arr[0][%d]:%x, p1[%d]:%x, arr1[%d]:%x\n", i, p_arr[0][i], i, p1[i], i, arr1[i]);

    // p_arr[1]��? p2�� �� == arr2�� �����ּ�
    printf("p_arr[1]:%p, p2:%p, arr2:%p\n", p_arr[1], p2, arr2);

    // p_arr[1][i]��? p2�� ������ �ּҿ��� i��° ������ �� == arr2[i]
    for (i = 0; i < 3; i++)
        printf("p_arr[1][%d]:%x, p2[%d]:%x, arr2[%d]:%x\n", i, p_arr[1][i], i, p2[i], i, arr2[i]);
    
    return 0;
}