import sys
import math

W, H = [int(i) for i in input().split()]
C    = int(input())
out  = []

for i in range(H): out.append(input())
for j in range(C):
    for i in range(len(out)): out[i] = sorted(out[i], reverse=True)
    out = list(zip(*out))

for r in out: print(''.join(r))
