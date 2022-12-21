// Question-6. 다음 수식을 참고하여 피보나츠(Fibonacci) 수를 구하는 함수 fibo()를 재귀함수로
// 작성하십시오. 0번째부터 10번째까지의 모든 피보나츠 수를 출력하는 C 프로그램을 작성하십시오. Write a
// recursive function fibo() to find the Fibonacci number with reference to the following equation. Write a C program that
// outputs all the Fibonacci numbers from the 0th to the 10th.
// • Fibonacci number: Fn = Fn-1 + Fn-2, F1 = 1, F0 = 0;

#include <stdio.h>

int fibo(int num)
{
    if (num == 0)
        return 0;

    if (num == 1 || num == 2)
        return 1;

    return fibo(num - 1) + fibo(num - 2);
}

int main()
{
    for (int i = 0; i < 11; i++)
    {
        printf("The %3d_th Fibonacci number is %6d.\n", i, fibo(i));
    }

    return 0;
}