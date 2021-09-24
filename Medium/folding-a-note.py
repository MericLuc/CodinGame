n = int(input())
p = [list(input()) for _ in range(n)]

while len(p[0]) > 1:
    tmp  = []
    for c in p:
        tmp.append([c[~i][::-1]+c[i] for i in range(len(c)//2)])
    p = list(zip(*tmp))[::-1]
print(p[0][0])
