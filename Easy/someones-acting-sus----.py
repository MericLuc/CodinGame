L   = int(input())
o   = input()
N,_ = map(int, input().split())
for _ in range(N):
    p   = input().strip('#')
    sus = False
    j   = 0
    i   = d = 1
    while i<len(p ):
        if p [i]=='#':
            d += 1
        else:
            dmin = (o  .index(p [j])-o  .index(p [i]))%L
            dmin = min(dmin, L-dmin)
            if d<dmin:
                sus = True
                break
            j = i
            d = 1
        i += 1
    print('SUS' if sus else 'NOT SUS')