// Question-1 다음과 조건을 만족하도록 가변인자 함수를 처리하는 C 프로그램을 작성하고자 합니다. 아래
// 프로그램의 빈 네모상자 부분에 들어갈 소스를 작성하시오. You want to write a C program that processes
// variadic argument functions to satisfy the following conditions. Write the source for the empty square box
// of the program below.
// • 가변인자를 처리하는 함수 vasum()의 다음 함수원형에서 첫 인자는 처리유형을 나타내는
// 문자열 포인터로 문자 d 이면 int 가 가변인자의 자료형이며, 문자 f 이면 double 이
// 가변인자의 자료형이며, 가변인자의 수는 문자열의 수만큼으로 처리하며, 가변인자의 합을
// 반환하는 함수. In the next function prototype of vasum(), a function that
// handles variadic arguments, the first argument is a string pointer
// indicating the type of processing. If the letter d is the type, int is the
// type of the variadic argument. The number is treated as the number of
// strings, and a function that returns the sum of variadic arguments.
// double vasum(char *, ...);
// • 함수 main()에서 다음을 호출하여 그 결과를 출력되도록 하며, 첫 인자인 문자열 “dfdf”는
// 가변인자가 순서대로 int, double, int, double 임을 나타내며 인자의 수는 4 개인 것을
// 표현. The function main() calls the following to output the result, and
// the first argument, the string “dfdf”, indicates that the variadic
// arguments are int, double, int, double in order, and the number of
// arguments is 4
//  vasum("dfdf", 3, 20.75412, 51, 21.9012);

#include <stdio.h>
#include <stdarg.h>
double vasum(char *, ...);
int main(void)
{
    double result = vasum("dfdf", 3, 20.75412, 51, 21.9012);
    printf("%.2f\n", result);
    return 0;
}
/* Variadic function to sum integer and real numbers */
double vasum(char *parm, ...)
{
    va_list my_list;
    va_start(my_list, parm);
    int i = 0;
    double sum_data = 0.0;
    while (*(parm + i))
    {
        switch (*(parm + i++))
        {
        case 'd':
            sum_data += va_arg(my_list, int);
            break;
        case 'f':
            sum_data += va_arg(my_list, double);
            break;
        default:
            break;
        }
    }
    // End processing for variadic arguments.
    va_end(my_list);
    // Returns the sum of all variadic arguments.
    return sum_data;
}