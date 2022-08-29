# (nice) Solution from schachmatt

import sys
import math
from functools import reduce

p1, p2 = input().split()
ratio = ["".join(sorted(s)) for s in input().split(":")]
counts = {x:0 for x in ratio}

a,b,c,d = p1; p1 = [a+c, a+d, b+c, b+d]
a,b,c,d = p2; p2 = [a+c, a+d, b+c, b+d]

for x in p1:
    for y in p2:
        z = "".join(sorted(x+y))
        if z in counts:
            counts[z] += 1

g = reduce(math.gcd, counts.values())

print(*[counts[x]//g for x in ratio], sep=":")