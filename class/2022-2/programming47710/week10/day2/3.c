// Question-3 표준입력으로 받은 두 실수의 사칙연산을 수행하는 다음 제한조건들을 만족하는 C 프로그램
// 을 작성하십시오. 아래 프로그램의 빈 네모상자 부분에 들어갈 소스를 작성하시오. Please write a C
// program that satisfies the following constraints to perform arithmetic operations on two real numbers
// received as standard input. Write the source for the empty square box of the program below.
// (Constraint-1) 사칙연산을 수행하는 함수를 모두 4 개 정의하여 이를 함수 포인터 배열에 저장한다.
// Define 4 functions that perform four arithmetic operations and store them in an array of function pointers.
// (Constraint-2) 사칙연산 중에서 하나의 연산을 다음과 같이 표준입력으로 받는다. One of the four
// arithmetic operations is received as standard input as follows
// Input/Output example:
// Enter the number for each operation for the four arithmetic operations.
// [Add]: 0, [Subtract]: 1, [Multiply]: 2, [Divide]: 3 >> 0
// Enter two real numbers to perform the arithmetic operation. >> 12.3 45.6
// Calling function: pfary[0]
//  result: 12.300000 + 45.600000 == 57.900000
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

void add(double *, double, double);
void subtract(double *, double, double);
void multiply(double *, double, double);
void devide(double *, double, double);

int main(void)
{
    double m, n, result;
    int opmenu;
    char op[4] = {'+', '-', '*', '/'};
    void (*pfary[4])(double *, double, double) = {add, subtract, multiply, devide};

    /* Declare an array of function pointers */
    printf("Enter the number for each operation for the four arithmetic operations.\n");
    printf("[Add]: 0, [Subtract]: 1, [Multiply]: 2, [Divide]: 3 >> ");
    scanf("%d", &opmenu);

    if (!(0 <= opmenu && opmenu <= 3))
    {
        printf("Wrong menu! The program stoped\n");
        return 0;
    }

    printf("Enter two real numbers to perform the arithmetic operation. >> ");
    scanf("%lf %lf", &m, &n);
    // Perform four arithmetic operations using the subscripts of the array

    pfary[opmenu](&result, m, n);
    /* Call the function with a function pointer */
    printf("\nCalling function: pfary[%d]\n", opmenu);
    printf(" result: %lf %c %lf == %lf\n\n", m, op[opmenu], n, result);
    return 0;
}

void add(double *z, double x, double y)
{
    *z = x + y;
}
void subtract(double *z, double x, double y)
{
    *z = x - y;
}
void multiply(double *z, double x, double y)
{
    *z = x * y;
}
void devide(double *z, double x, double y)
{
    *z = x / y;
}