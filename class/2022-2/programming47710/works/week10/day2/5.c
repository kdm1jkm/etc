// Question-5 다음과 조건을 만족하도록 가변인자 함수를 처리하는 C 프로그램을 작성하고자 합니다. 아래
// 프로그램의 빈 네모상자 부분에 들어갈 소스를 작성하시오. You want to write a C program that processes
// a variadic argument to satisfy the following conditions. Write the source for the empty square box of the
// program below.
// • 가변인자를 처리하는 함수 vafunc()의 다음 함수원형에서 첫 인자는 처리유형으로 문자 d 이면
// int 가 가변인자의 자료형이며, 문자 f 이면 double 이 가변인자의 자료형이며, 첫 인자는
// 가변인자의 개수를 지정하며, 가변인자의 평균을 반환하는 함수. In the following function
// prototype of vafunc(), a function that handles variadic arguments, the first argument is the
// processing type, and if the letter d is the type, int is the data type of the variadic argument, if
// the letter f, the double is the data type of the variadic argument, and the first argument is the
// number of variadic arguments. It specifies and returns the average of variadic arguments.
// double vafunc(char *type, int count, ...); // ... is variadic arguments

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

// Include a head file for handling variadic argument
double vafunc(char *type, int count, ...);

int main(void)
{
    printf("Average %.2f\n", vafunc("d", 5, 172, 21, 36, 43, 58));
    printf("Average %.2f\n", vafunc("f", 5, 5.8, 17.3, 2.8, 31.8, 45.9, 5.9));
    return 0;
}

double vafunc(char *type, int count, ...)
{
    // Assign a name for the variadic argument
    va_list argp;

    // Begin to process the variadic argument
    va_start(argp, count);

    double total = 0;
    for (int i = 0; i < count; i++)
        switch (*(type))
        {
        case 'd': // Get an argument in specified data type one by one
            total += va_arg(argp, int);
            break;
        case 'f': // Get an argument in specified data type one by one
            total += va_arg(argp, double);
            break;
        default:
            break;
        }
    // End of the processing the variadic argument
    va_end(argp);
    return total / count;
}