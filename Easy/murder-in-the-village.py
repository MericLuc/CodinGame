P=[[a, b, 0] for _ in range(int(input())) for a,b in [input().split(': I was in the ')]]
for i,(n,m,_) in enumerate(P):
    for nm, al, _ in P:
        if n!=nm and n in al and m[:3] in al:
            P[i][2] = 1
            break
        elif m[-6::] == 'alone.' and n in al:
            print(nm, 'did it!')
            quit()
        elif n!=nm and m[-6::] == 'alone.' and m[:3] in al:
            print(n, 'did it!')
            quit()
ret = [n for n,m,c in P if c==0]
if len(ret)>1: ret = [n for n,m,c in P if c==0 if 'alone' not in m]    
print(ret[0]+' did it!' if ret else 'It was me!')