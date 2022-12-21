// Question-3. 표준입력으로 부터 정수를 “%s”로 입력받아, 숫자로 변환한 후 “%d”로 출력하는 프로그램을
// 작성하시오. <stdlib.h>에 정의되어 있는 int atoi(const char *string) 를 사용하여 그 입력
// 문자열을 변환한 결과도 함께 출력하십시오.
// Write a program that receives integers as “%s” from standard input, converts them to numbers, and
// outputs them as “%d”. Also print the result of converting the input string using int atoi(const char
// *string) defined in <stdlib.h>.

#include <stdio.h>
#include <stdlib.h>

#define N 10

int my_atoi(char *str);

int main(void)
{
    char num[N];
    char *p = num;
    printf("Enter an integer number : ");
    scanf("%s", num);

    printf("Using my_atoi : %d\n", my_atoi(num));
    printf("Using atoi lib: %d\n", atoi(num));

    return 0;
}
int my_atoi(char *str)
{
    int result = 0;

    int index = 0;
    char c;
    while ((c = str[index++]) != '\0')
    {
        result *= 10;
        result += (c - '0');
    }

    return result;
}