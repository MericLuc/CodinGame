n   = int(input())
res = 0
cpy = n
p = 2
while p <= cpy:
    while cpy % p == 0:
        cpy //= p
        res += n // p
    p += 1
print(res)