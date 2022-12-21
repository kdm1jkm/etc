// Question-1. 다음 문장에서 실행결과가 다른 하나의 문장은 어느 것인가? Which sentence of the
// followings has a different execution result?
// char s[] = "123456";
// char *d = "123456";
// A) printf("%d\n", strlen(s));
// B) printf("%d\n", strlen(d));
// C) printf("%d\n", sizeof(s));
// D) printf("%c\n", *(d + strlen("12345")));

#include <stdio.h>

int main()
{
    char s[] = "123456";
    char *d = "123456";
    printf("%d\n", strlen(s));
    printf("%d\n", strlen(d));
    printf("%d\n", sizeof(s));
    printf("%c\n", *(d + strlen("12345")));
}
