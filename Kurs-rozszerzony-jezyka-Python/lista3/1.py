from functools import reduce
import timeit

def imperatywna (n):
    is_prime = [True] * (n + 1)
    prime_numbers = list(range(0, n + 1))

    is_prime[0] = is_prime[1] = False

    for liczba in range(2, int(n ** 0.5) + 1):
        if not is_prime[liczba]:
            continue
        for liczba2 in range(liczba * liczba, n + 1, liczba):
            if is_prime[liczba2]:
                is_prime[liczba2] = False
                prime_numbers.remove(liczba2)
    return prime_numbers

def skladana (n):
    pom = [i*j for i in range (2, int(n** 0.5)+1) for j in range((i**2), n, i)]
    return [i for i in range(2, n) if i not in pom]

def funkcyjna (n):
    def sieve(nums, i):
        return list(filter(lambda x: x == i or x % i != 0, nums))
    return reduce(sieve, range(2, int(n**0.5) + 1), list(range(2, n)))

num = 100  
width = 12

print(f"{'n ':>{width}} {'skladana':>{width}} {'imperatywna':>{width}} {'funkcyjna':>{width}}")

for n in range(10,510,10):
    t_skladana = timeit.timeit(lambda: skladana(n), number=num)
    t_imperatywna = timeit.timeit(lambda: imperatywna(n), number=num)
    t_funkcyjna = timeit.timeit(lambda: funkcyjna(n), number=num)
    
    print(f"{str(n)+':':>{width}} {t_skladana/num:>{width}.5f} {t_imperatywna/num:>{width}.5f} {t_funkcyjna/num:>{width}.5f}")