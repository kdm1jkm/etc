#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int sum(int n);
int _sum(int n);
int main(void)
{
    int num;
    printf("Enter a positive integer : ");
    scanf("%d", &num);
    printf("sum = %d\n", sum(num));
    printf("sum = %d\n", _sum(num));
    return 0;
}
int sum(int n)
{
    static int called;
    printf("The function sum() was called %d-times\n", ++called);
    if (n == 1)
        return 1;
    return sum(n - 1) + n;
}

// 같은 일을 다르게 수행
int _sum(int n)
{
    for (int i = 0; i < n; i++)
        printf("The function _sum() was called %d-times\n", i + 1);

    return n * (n + 1) / 2;
}