// Question-6. 한 행을 표준입력으로 입력 받은 문자열의 길이를 구하는 함수 mystrlen()을 구현하여
// 라이브러리 strlen()과 결과를 비교하는 프로그램을 작성하십시오. 입출력 예를 참고하십시오.
// • int mystrlen(const char *p)
// • 한 행을 표준입력으로 입력 받는 것은 라이브러리 gets_s() 사용
// Implement the function mystrlen() that calculates the length of the string received as standard input
// for a line. And write a program that compares the result with the library strlen(). Please refer to the
// input/output example.
// 페이지 2 / 2
// • int mystrlen(const char *p)
// • To get a line as standard input, use the library gets_s().
// Input/Output example:
// Enter any string : Good morning
// Using mystrlen, 'Good morning' is : 12
// Using strlen, 'Good morning' is : 12
// Your answer should be as follows:
#define _CRT_SRCURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
int mystrlen(char *);
int main(void)
{
    char str[80];
    printf("Enter any string : ");
    gets_s(str, 80); // You should write your codes here
    printf("Using mystrlen, '%s' is : %d\n", str, mystrlen(str));
    printf("Using strlen, '%s\' is : %d\n", str, strlen(str));
    return 0;
}

int mystrlen(char *p)
{
    int len = 0;
    while (*(p++) != '\0')
    {
        len++;
    }
    return len;
}