/*
 * 문제5. 다음 조건을 만족하는 프로그램을 작성하시오.
 * (조건 1) 변수 point1 을 선언하여 중간고사 성적인 95 를 저장, 변수 point2 를 선언하여 기말고사
 * 성적인 84 를 저장
 * (조건 2) 두 수의 합을 변수 total 에 저장하여, 두 수와 합을 적절히 출력
 */

#include <stdio.h>

int main()
{
    int point1 = 95;
    int point2 = 84;

    int total = point1 + point2;

    printf("중간고사: %d, 기말고사: %d\n", point1, point2);
    printf("합계: %d\n", total);

    return 0;
}