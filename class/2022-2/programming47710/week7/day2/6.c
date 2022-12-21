// Question-6. 다음과 같이 외부 변수를 선언하면서 초기 값을 지정하는 것이 가능한지 알아보는
// 프로그램을 작성하십시오. 만일 문제가 있다면 해결 방법을 제시하십시오. Write a program to
// see if it is possible to designate an initial value while declaring an external variable as follows. If
// there is a problem, please provide a solution.

#include <stdio.h>

extern int x = 10; // Warning

int main()
{
    printf("x: %d\n", x);
}