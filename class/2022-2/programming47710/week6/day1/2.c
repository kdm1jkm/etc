// Question-2. 앞의 문자열 s1에 뒤 문자열 s2을 연결하는 함수 mystrcat()를 구현하여 라이브러리
// strcat()과 결과를 비교하는 프로그램을 작성하시오.
// Implement a function mystrcat() that concatenates the previous string s1 to the next string s2, and write a program that
// compares the results with the library strcat().
// #define _CRT_SECURE_NO_WARNINGS
// void mystrcat(char s1[], char s2[]);
// char s1[100] = "C ";
// char s2[50] = "programming language";

#include <stdio.h>
#include <string.h>

void mystrcat(char s1[], char s2[])
{
    int len = strlen(s1);
    int index = 0;
    char c;
    while ((c = s2[index++]) != '\0')
        s1[len + index] = c;
}

int main()
{
    char s1[100] = "C ";
    char s2[50] = "programming language";

    strcat(s1, s2);
    printf("strcat: %s\n", s1);

    strcpy(s1, "C ");
    mystrcat(s1, s2);
    printf("mystrcat: %s\n", s1);

    return 0;
}
