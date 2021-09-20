# Initial solution from icecuber
def get(c):
    p = []
    for i in range(3):
        for j in range(3):
            p.append((c[  i][ 4+j], (  j, 0, 2-i), (  i, 4+j)))
            p.append((c[4+i][   j], (  0, i, 2-j), (4+i,   j)))
            p.append((c[4+i][ 4+j], (  j, i,   0), (4+i, 4+j)))
            p.append((c[4+i][ 8+j], (  2, i,   j), (4+i, 8+j)))
            p.append((c[4+i][12+j], (2-j, i,   2), (4+i,12+j)))
            p.append((c[8+i][ 4+j], (  j, 2,   i), (8+i, 4+j)))

    ret = []
    for col, d3, d2 in p:
        context = []
        for colb, coordb, _ in p:
            if coordb == d3:
                context.append(colb)
        context.sort()
        ret.append((col, d2, context))
    return ret

in_flat = [input() for i in range(11)]
solved_flat = """    UUU
    UUU
    UUU

LLL FFF RRR BBB
LLL FFF RRR BBB
LLL FFF RRR BBB

    DDD
    DDD
    DDD""".split('\n')

out_flat = [list(row) for row in solved_flat]

in_cube = get(in_flat)
solved  = get(solved_flat)

for cola, coorda, contexta in in_cube:
    for colb, coordb, contextb in solved:
        if cola == colb and contexta == contextb:
            ra,ca = coorda
            rb,cb = coordb
            out_flat[rb][cb] = solved_flat[ra][ca]

for row in out_flat:
    print(''.join(row))