// 문제2. double 형의 두 실수들을 표준입력으로 받아서 사칙연산(덧셈, 뺄셈, 곱셈, 나눗셈)을 수행하는
// 프로그램을 작성하십시오.
// (조건 1) 표준입력을 위해 scanf_s()를 사용하십시오.
// (조건 2) 두 개의 double 형 변수들 x 와 y 를 선언하고 표준 입력으로 부터 그 값들을 입력한다.
// (조건 3) 두 개의 double 형 포인터 변수들 px 와 px 를 선언하고,위 두 수들에 대한 사칙연산을
// 수행한다.
// Question-2. Write a program that takes two real numbers of data-type double from standard inputs and performs
// four arithmetic operations (add, subtract, multiply, divide).
// (Condition 1) Use scanf_s() for standard input.
// (Condition 2) Declare two double variables, x and y, and enter their values from standard input.
// (Condition 3) Declares two double pointer variables, px and py, and performs four arithmetic operations on the two
// numbers above.

#include <stdio.h>

int main()
{
    double x, y;
    printf("Enter two real numbers: ");
    scanf("%lf %lf", &x, &y);

    double *px = &x, *py = &y;

    printf("%.2lf + %.2lf = %.2lf\n", *px, *py, *px + *py);
    printf("%.2lf - %.2lf = %.2lf\n", *px, *py, *px - *py);
    printf("%.2lf * %.2lf = %.2lf\n", *px, *py, *px * *py);
    printf("%.2lf / %.2lf = %.2lf\n", *px, *py, *px / *py);
}