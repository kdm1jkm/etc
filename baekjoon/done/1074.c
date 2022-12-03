#include <stdio.h>

unsigned long long _pow(unsigned long long a, unsigned long long b)
{
    unsigned long long result = 1;
    for (unsigned long long i = 0; i < b; i++)
        result *= a;
    return result;
}

unsigned long long calc(unsigned long long n, unsigned long long r, unsigned long long c)
{
    if (n == 2)
    {
        return r * 2 + c;
    }
    n /= 2;
    return calc(n, r % n, c % n) + n * n * calc(2, r / n, c / n);
}

int main()
{
    unsigned long long n, r, c;
    scanf("%llu %llu %llu", &n, &r, &c);

    printf("%llu\n", calc(_pow(2, n), r, c));
}