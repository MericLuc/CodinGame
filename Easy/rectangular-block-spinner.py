import sys
import numpy as np

S = int(input())
A = int(input())

d = np.loadtxt(sys.stdin, comments=None, dtype=str)
d = np.rot90(d, k=(A-45)/90%4)

for i in range(S-1,-S,-1):
    sp = " "*abs(i)
    print(sp + " ".join(d.diagonal(i)) + sp)