/*
 * 문제4. 표준입력으로 문자를 하나 입력 받아 다음 조건을 만족하는 프로그램을 작성하시오.
 * (조건) 입력된 문자의 문자, 8진수 코드 값, 10진수 코드 값, 16진수 코드 값 출력
 */

#include <stdio.h>

int main()
{
    char c;
    printf("문자 입력: ");
    scanf("%c", &c);

    printf("%c %o %d %x\n", c, c, c, c);
    // 8, 16진수 접두사
    printf("%c %#o %d %#x\n", c, c, c, c);

    return 0;
}