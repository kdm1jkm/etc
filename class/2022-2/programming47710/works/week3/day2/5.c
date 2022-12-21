// Question-5. 여러가지 값의 n 에 대하여, 1 부터 n 까지의 합계 값들 중에서 2,000 을 넘지 않는 가장 큰
// 합계 값을 출력하고, 또, 그 때의 n 을 출력하는 C-프로그램을 작성하십시오. 다만, 반복문으로 dowhile 문을 사용하십시오. Write a C-program that outputs the largest summation not exceeding 2,000 among the
// summations of 1 to n for various values of n, and also outputs n at that time. However, use the “do-while” statement
// as a loop.

#include <stdio.h>

int main()
{
    int n;
    printf("Enter: ");
    scanf("%d", &n);

    int sum = 0;
    int i = 0;
    do
    {
        sum += ++i;
    } while (sum <= 2000 && i <= n);

    sum -= i--;

    printf("Sum: %d\nn: %d\n", sum, i);

    return 0;
}