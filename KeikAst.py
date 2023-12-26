def binomial_coefficient(n, m, p, factorial, denominator_inverses):
    numerator = factorial[n]
    denominator_inverse = (denominator_inverses[m] * denominator_inverses[n - m]) % p
    return (numerator * denominator_inverse) % p


# Main Program
t, p = map(int, input().split())
n_array = []
m_array = []
max_n = 0
for _ in range(t):
    n, m = map(int, input().split())
    n_array.append(n)
    m_array.append(m)

max_n = max(n_array)
factorial = [0] * (max_n + 1)
denominator_inverses = [0] * max_n
factorial[0] = 1

for i in range(1, max_n + 1):
    factorial[i] = (factorial[i - 1] * i) % p

denominator_inverses[max_n - 1] = pow(factorial[max_n - 1], p - 2, p)

for i in range(max_n - 2, -1, -1):
    denominator_inverses[i] = (denominator_inverses[i + 1] * (i + 1)) % p

for i in range(t):
    result = binomial_coefficient(n_array[i], m_array[i], p, factorial, denominator_inverses)
    print(result)
