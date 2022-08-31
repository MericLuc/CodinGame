import math

m = int(input())-1
n = int(input())-1

print(str(math.comb(m+n,n))[:1000])