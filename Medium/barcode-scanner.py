import sys 

def chksm(dg):
    return sum(int(dg[i])*[1,3][i%2] for i in range(len(dg)))%10 == 0
    
def parity(side):
    p = ''.join('L' if p.count('1')%2 else 'G' for p in side)
    if p == 'G'*6: return 'R'*6
    return p    
    
def cs(bs, start):
    CODE_SIZE = 7
    return [bs[i:i+CODE_SIZE] for i in range(start, start+CODE_SIZE*6, CODE_SIZE)]

L      = ['0001101', '0011001', '0010011', '0111101', '0100011', '0110001', '0101111', '0111011', '0110111', '0001011']
R      = [''.join('0' if i=='1' else '1' for i in l) for l in L]
G      = [r[::-1] for r in R]
ppat   = ['LLLLLL', 'LLGLGG', 'LLGGLG', 'LLGGGL', 'LGLLGG', 'LGGLLG', 'LGGGLL', 'LGLGLG', 'LGLGGL', 'LGGLGL']
pright = 'RRRRRR'
LG_map = {'G':G, 'L':L}

def ean13_dec(barc):
    err = False
    lg, cg, rg = barc[:3], barc[45:50], barc[-3:]
    if lg+cg+rg == '10'*5+'1':
        right = cs(barc, 50)
        if parity(right) != pright:
            barc = barc[::-1]
            right = cs(barc, 50)
        if parity(right) != pright:
            err = True
        else:
            left = cs(barc, 3)
            pleft = parity(left)
            dg = []
            if pleft in ppat:
                dg += [ppat.index(pleft)]
                for p in pleft:
                    c = left.pop(0)
                    if c in LG_map[p]:
                        dg += [LG_map[p].index(c)]
                    else:
                        err = True
                        break
                for c in right:
                    if c in R:
                        dg += [R.index(c)]
                    else:
                        err = True
                        break
                if not err and not chksm(dg):
                    err = True
            else:
                err = True
    else:
        err = True
    
    return '' if err else ''.join(map(str, dg))

def ean13_enc(dg):
    lrg = '101'
    cg = '01010'
    parity = list(ppat[int(dg[0])])
    c = lrg
    for i in dg[1:7]:
        c += LG_map[parity.pop(0)][int(i)]
    c += cg
    for i in dg[7:]:
        c += R[int(i)]
    c += lrg
    return c

dg = ean13_dec(input())
print(dg if dg else 'INVALID SCAN')
