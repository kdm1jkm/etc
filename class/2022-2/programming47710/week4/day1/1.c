// 문제1. 다음 조건을 만족하는, char 형 포인터에 관한 프로그램을 작성하십시오.
// (조건 1) 변수를 선언하여 문자 ‘A’를 저장한다.
// (조건 2) 포인터 변수를 선언하여 위 변수의 주소, 16 진수 형태의 ASCII 코드 값, 그리고 그 문자를
// 출력한다.
// Question-1. Write a program for a pointer of data-type char that satisfies the following conditions.
// (Condition 1) Declare a variable and store the character 'A'.
// (Condition 2) Declare a pointer variable and output the address, hexadecimal ASCII code value, and the character of
// the above variable.

#include <stdio.h>

int main()
{
    char c = 'A';

    char *p = &c;
    printf("%p %#x %c\n", p, *p, *p);
}