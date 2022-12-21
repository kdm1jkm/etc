// Question-6. 반복문으로 for문을 문을 사용하여, 앞의 Question-5을 풀이하십시오. Solve the Question-5
// using the "for" statement as a loop.

#include <stdio.h>

int main()
{
    int n;
    printf("Enter: ");
    scanf("%d", &n);

    int sum = 0;

    for (int i = 1; i <= n; i++)
    {
        if (sum > 2000)
        {
            sum -= --i;
            n = --i;
            break;
        }

        sum += i;
    }

    printf("Sum: %d\nn: %d\n", sum, n);

    return 0;
}