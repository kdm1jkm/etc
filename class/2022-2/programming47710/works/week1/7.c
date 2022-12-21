/*
 * 문제7. 두 실수를 표준입력으로 입력 받아 다음 조건을 만족하는 프로그램을 작성하시오.
 * (조건 1) 두 실수가 가로, 세로인 사각형의 면적을 전체 폭 12, 소수 이하 3 자리, 우측정렬로 출력
 * (조건 2) 두 실수가 밑변, 높이인 삼각형의 면적을 전체 폭 12, 소수 이하 3 자리, 좌측정렬로 출력
 */

#include <stdio.h>

int main()
{
    double num1, num2;

    printf("Enter num1: ");
    scanf("%lf", &num1);
    printf("Enter num2: ");
    scanf("%lf", &num2);

    double rectangle = num1 * num2;
    double triangle = num1 * num2 / 2;

    printf("%12.3lf\n", rectangle);
    printf("%-12.3lf\n", triangle);

    return 0;
}