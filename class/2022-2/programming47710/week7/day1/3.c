// Question-3. 레지스터 변수는 초기 값을 지정하지 않을 경우 기본 값이 있는지 알아보는 C프로그램을
// 작성하시오. Please write a C program to check if there is a default value for a register variable when you
// do not designate an initial value.

#include <stdio.h>

int main()
{
    for (int i = 0; i < 100; i++)
    {
        register int v;
        printf("[#%02d] v = %d\n", i, v);
    }
    return 0;
}