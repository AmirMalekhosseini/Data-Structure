def multiply_matrices(a, b, n, m, k):
    result = [[1] * k for _ in range(n)]

    for i in range(n):
        for j in range(k):
            for x in range(m):
                result[i][j] *= a[i][x] + b[x][j]  # Multiply instead of Sum

            if result[i][j] > 13800905:
                result[i][j] %= 13800905

    return result


n, m, k = map(int, input().split())

a = []
for _ in range(n):
    row = list(map(int, input().split()))
    a.append(row)

b = []
for _ in range(m):
    row = list(map(int, input().split()))
    b.append(row)

# Multiply matrices A and B
result = multiply_matrices(a, b, n, m, k)

for row in result:
    for element in row:
        print(element % 13800905, end=' ')
    print()