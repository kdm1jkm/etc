// Question-4. 지불할 금액을 정수로 입력 받아 화폐단위가 각각 몇 개씩 필요한지 출력하는 프로그램을
// 작성하십시오. Write a program that takes the amount to be paid as an integer and that outputs how many currency units
// are needed.
// (Constraint-1) 입력은 최소 천원 단위로 입력한다. Enter at least in units of 1,000 won
// (Constraint-2) 화폐단위는 50000, 10000, 5000, 1000 의 4 가지이며, 가능한 큰 화폐단위로 지불한다.
// There are 4 types of currency units: 50000, 10000, 5000, and 1000. We will make payment in the largest possible
// currency unit.
// (Constraint-3) 예를 들면, 입력이 236000 이면, 50000 원권 4 개, 10000 원권 3 개, 5000 원권 1 개,
// 1000 원권 1 개로 출력한다. For example, if the input is 236000, we will print 4 50000-won notes, 3 10000-won
// notes, 1 5000-won notes, 1 1000-won notes.

#include <stdio.h>

int main()
{
    int amount;
    printf("Enter: ");
    scanf("%d", &amount);

    const int units[] = {50000, 10000, 5000, 1000};
    const int unitCount = 4;

    int counts[4];

    for (int i = 0; i < unitCount; i++)
    {
        counts[i] = amount / units[i];
        amount %= units[i];
    }

    for (int i = 0; i < unitCount; i++)
    {
        printf("%d원권 %d개, ", units[i], counts[i]);
    }

    return 0;
}