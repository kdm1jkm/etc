// Question-5 다음 프로그램에서 컴파일 오류, 논리오류 및 실행 오류를 찾아 수정하십시오. Find and
// correct compilation errors, logic errors, and execution errors in the following programs.
#include <stdio.h>
#include <string.h>
int main(void)
{
    struct data
    {
        char ch[4];
        int cnt;
    } u1;
    struct data u2 = {"C++", 100};
    strcpy(u1.ch, "C");
    u1.cnt = 200;
    printf("%s\n", u1.ch);
    printf("%d\n", u2.cnt);
    return 0;
}