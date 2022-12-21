// Question-6. 원금이 1,000,000원이고, 연이자율이 2.5%이고, 은행에 그 원금을 예금하여 10년 뒤에 찾을
// 경우, 원금과 복리 이자의 합계 가 얼마인지를 출력하는 C 프로그램을 작성하십시오. Write a C program
// that prints the sum of the principal and compound interest if the principal is 1,000,000 won, the annual
// interest rate is 2.5%, and you deposit the principal in a bank and withdraw it 10 years later.
// (Constraint) Use the library pow(a, b) = ab . It is defined in <math.h> .

#include <stdio.h>
#include <math.h>

int main()
{
    const int principal = 1000000;     //원금
    const double interestRate = 0.025; //이자율
    const int period = 10;             //기간

    double compoundInterest = principal * pow(1 + interestRate, period) - principal;
    printf("total: %f\n", principal + compoundInterest);

    return 0;
}