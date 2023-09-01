import re
import math

pattern = r'(.+)\(([^)]+)\)'
d       = int(input())
n       = int(input())
v       = {}

for i in range(n):
    match = re.match(pattern, input())
    v[match.group(1)] = tuple(map(int, match.group(2).split(',')))

NAME = "name"
VAL  = "val"
DIST = "dist"

min_result = { NAME:"", VAL:(), DIST:float('inf') }
max_result = { NAME:"", VAL:(), DIST:0.           }

for k1,v1 in v.items():
    for k2,v2 in v.items():
        if k2 == k1: 
            continue
        name = f"{k1}{k2}"
        val  = tuple(y - x for x, y in zip(v1, v2))
        dist = math.sqrt(sum(x**2 for x in val))

        if dist < min_result[DIST]:
            min_result = {NAME: name, VAL: val, DIST: dist}
        if dist > max_result[DIST]:
            max_result = {NAME: name, VAL: val, DIST: dist}

print('{}({})'.format(min_result[NAME], ','.join(map(str, min_result[VAL]))))
print('{}({})'.format(max_result[NAME], ','.join(map(str, max_result[VAL]))))