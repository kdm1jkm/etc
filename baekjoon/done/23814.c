#include <stdio.h>

int main()
{
    long long int d, n, m, k;
    scanf("%lld %lld %lld %lld", &d, &n, &m, &k);

    n %= d;
    m %= d;

    m = d - m;
    n = d - n;

    if (n > m)
    {
        int temp = n;
        n = m;
        m = temp;
    }

    long long int require = m + n;
    long long int extra = k % d;

    if (require <= extra)
    {
        k -= require;
    }
    else if (n <= extra)
    {
        k -= n;
    }
    else if (require <= extra + d)
    {
        k -= require;
    }

    printf("%lld\n", k);

    return 0;
}