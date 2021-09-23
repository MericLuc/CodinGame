input()
pt = input()
input()
st = input()
h, _ = map(int, input().split())
for i in range(h):
    res = ""
    depth = pos = 0
    p, s = list(pt), list(st)
    for d in map(int,input()):
        for n in range(d - depth):
            del p[pos]
            pos = pos % len(p)
        for n in range(depth - d):
            p.insert(pos+n,s.pop(0))
        res += p[pos]
        pos = (pos+1)%len(p)
        depth = d
    print(res)