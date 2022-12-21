/*
 * 문제2. 표준입력으로 4자리 정수를 하나 입력 받아 다음 조건을 만족하는 프로그램을 작성하시오.
 * (조건 1) 만일 입력이 6527 이라면 다음과 같은 입출력이 되도록
 * (조건 2) 모두 전체폭은 10
 */

#include <stdio.h>

int main()
{
    int num;
    printf("4자리 정수 입력: ");
    scanf("%d", &num);

    printf("%10d\n", num);
    printf("%010d\n", num);
    printf("%+010d\n", num);
    printf("%-10d\n", num);

    printf("%10o\n", num);
    printf("%010o\n", num);

    printf("%10x\n", num);
    printf("%#010x\n", num);

    return 0;
}