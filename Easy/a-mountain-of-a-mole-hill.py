S   = 16
res = 0
L   = ' '*S

for _ in range(S):
    L, L0 = input(), L
    inside = False
    for j,c in enumerate(L):
        if c=='|' or (c=='+' and L0[j] in '|+'): inside = not inside
        elif c=='o' and inside: res += 1
print(res)