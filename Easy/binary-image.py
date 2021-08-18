g = []
for _ in range(int(input())):
    g.append(''.join('.O'[i%2]*c for i,c in enumerate(map(int, input().split()))))
print('\n'.join(g) if all(len(l) == len(g[0]) for l in g) else 'INVALID' )
