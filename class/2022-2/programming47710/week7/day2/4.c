#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

unsigned int fib(unsigned int n);

int main(void)
{
    int num; // n < 10
    printf("Enter a positive integer (less than 10) : ");
    scanf("%d", &num);
    printf("fib(%d) = %d\n", num, fib(num));
    return 0;
}
unsigned int fib(unsigned int n)
{
    static int totalCalled;
    static int called[10];
    printf("\tfib(%d) was called %d-times. Total %2d-times called\n", n, ++called[n], ++totalCalled);

    if (n <= 1)
        return n;
    return fib(n - 1) + fib(n - 2);
}