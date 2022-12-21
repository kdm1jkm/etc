// Question-4 다음 내용을 참고로 구조체 fraction을 정의하고, 2개의 분수를 선언하여 적당한 값으로 초기
// 화하고, 그 들을 출력하는 프로그램을 작성하십시오. Define the structure fraction with reference to the
// following, declare two fractions, initialize them with appropriate values, and write a program that prints
// them.
// • 구조체 fraction 멤버 구성: 정수형의 분자와 분모. Structure fraction whose members are integer
// numerator and integer denominator.
#include <stdio.h>
struct fraction
{
    int numerator;
    int denominator;
};
int main(void)
{
    typedef struct fraction fraction;
    fraction a = {4, 5};
    fraction b = {3, 7};
    printf("%d / %d\n", a.numerator, a.denominator);
    printf("%d / %d\n", b.numerator, b.denominator);
    return 0;
}