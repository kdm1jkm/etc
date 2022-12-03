def is_prime(primes, n):
    for prime in primes:
        if n % prime == 0:
            return False
    return True


m, n = map(int, input().split())
primes = []
for i in range(2, n + 1):
    if is_prime(primes, i):
        primes.append(i)
        if i >= m:
            print(i)
