/*
 * 문제6. 표준입력으로 두 실수를 입력 받아 합과 평균을 구하여 출력하는 프로그램을 작성하시오.
 * (조건) 합과 평균 모두를 실수로 출력
 */

#include <stdio.h>

int main()
{
    double num1, num2;

    printf("Enter num1: ");
    scanf("%lf", &num1);
    printf("Enter num2: ");
    scanf("%lf", &num2);

    double sum = num1 + num2;

    printf("Sum: %lf, Average: %lf\n", sum, sum / 2);

    return 0;
}