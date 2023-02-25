# Inspired by Niako

def addCol(T, i, c):
    for L in T: L.append(' ')
    T[i][-1] = c

N   = int(input())
M   = [1] + list(map(int, input().split())) + [1]
m0  = min(M)
out = [[] for _ in range(max(M)-m0+1)]

for i in range(1, N + 2):
    if M[i-1] < M[i]:
        for k in range(M[i-1], M[i]):
            addCol(out, k-m0, '/')
    else:
        for k in range(M[i-1]-1, M[i]-1, -1):
            addCol(out, k-m0, '\\')
    addCol(out, M[i]-m0, '/')
    addCol(out, M[i]-m0, '\\')

for L in reversed(out):
    print(''.join(L[:-2]).rstrip())
