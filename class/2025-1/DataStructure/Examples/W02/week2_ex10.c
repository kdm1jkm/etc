/*
 * ������ �迭�� Ȱ�� #3
 */


#include <stdio.h>

int main(void) {
    int i;
    // 2���� �迭 ����
    int score[2][3] = {{0x30, 0x44, 0x67}, {0x87, 0x43}};

    /*
     �迭[i]�� �̸��� ���� ������ �ּ�, ���� ������ ������ �Ҵ� ����
     ���� �����͹迭�� ���ҿ� �迭�� �̸��� �Ҵ��� �� �ִ�.
    */
    int *p_arr[2] = { score[0], score[1] };

    int **pp_arr = p_arr;

    // p_arr[0]��? score[0]�� �� == score[0][0~1]�� �����ּ�
    printf("p_arr[0]:%p, score[0]:%p\n", pp_arr[0], score[0]);

    // p_arr[0][i]��? p_arr[0] ������ �ּ�(score[0])���� i��° ������ �� == score[0][i]
    for (i = 0; i < 3; i++)
        printf("p_arr[0][%d]:%x, score[0][%d]:%x\n", i, pp_arr[0][i], i, score[0][i]);

    // p_arr[1]��? score[1]�� �� == score[1][0~1]�� �����ּ�
    printf("p_arr[1]:%p, score[1]:%p\n", pp_arr[1], score[1]);

    // p_arr[1][i]��? p_arr[1] ������ �ּ�(score[1])���� i��° ������ �� == score[1][i]
    for (i = 0; i < 3; i++)
        printf("p_arr[1][%d]:%x, score[1][%d]:%x\n", i, pp_arr[1][i], i, score[1][i]);
    
    return 0;
}