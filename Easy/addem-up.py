N = int(input())
x = sorted(map(int, input().split()))

cost = 0
while len(x) > 1:
    minSum = x[0] + x[1]
    cost  += minSum
    x      = sorted([minSum] + x[2:])
print(cost)
