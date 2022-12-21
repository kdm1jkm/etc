// Question-3. 다음 내용을 참고로 프로그램의 빈 부분에 들어갈 소스를 작성하시오. Please fill the source
// in the blank part of the program referring to the following

#include <stdio.h>

// Global variable, total = 10000
int total = 10000;

void save(int);     // Function prototype for deposit
void withdraw(int); // Function prototype for withdraw

int main(void)
{
    printf("Deposit Withdraw Total_deposit Total_withdraw Balance\n");
    printf("====================================================\n");
    printf("%51d\n", total);
    save(50000);
    withdraw(30000);
    save(60000);
    withdraw(20000);
    printf("====================================================\n");
    return 0;
}
void save(int money)
{
    static int amount = 0; // amount, the static local variable to save the total deposit
    total += money;
    amount += money;
    printf("%7d %17d %25d\n", money, amount, total);
}
void withdraw(int money)
{
    static int amount = 0; // amount, the static local variable to save the total withdraw
    total -= money;
    amount += money;
    printf("%15d %22d %12d\n", money, amount, total);
}