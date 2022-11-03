#From CompOzr

n = int(input())

grid = [[0 for i in range(n)]for j in range(n)]

D = [[0, 1], [-1, 0], [0, -1], [1, 0]]

mid = n//2
y = mid
x = mid
d = 0
l = 0
i = 1

while i <= n*n:
    if d == 0: l += 1
    
    while x not in [-1, n] and y not in [-1, n]:
        grid[y][x] = i

        next_y = y + D[d][0]
        next_x = x + D[d][1]

        if abs(next_y - mid) > l or abs(next_x - mid) > l: break

        y = next_y
        x = next_x
        i += 1
        
    d = (d + 1) % 4       

for row in grid: print(*[' #'[x > 1 and all(x % i for i in range(2, x))] for x in row])