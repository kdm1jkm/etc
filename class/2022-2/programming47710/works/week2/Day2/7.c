// Question-7. 분 단위를 갖는 어떤 숫자를 입력 받아서, 그 것이 몇 일 몇 시간 몇 분에 해당하는지
// 출력하는 C프로그램을 작성하십시오. Write a C program that takes a number in minutes as input and
// outputs the number of days, hours, and minutes.
// (Example) 30,000 minutes is 20 days 20 hours 0 minutes.

#include <stdio.h>

int main()
{
    int minutes;
    printf("Enter minutes: ");
    scanf("%d", &minutes);

    printf("%d minutes is ", minutes);

    int hours = minutes / 60;
    minutes %= 60;

    int days = hours / 24;
    hours %= 24;

    printf("%d days %d hours %d minutes\n", days, hours, minutes);

    return 0;
}