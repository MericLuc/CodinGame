from itertools import product

lines = int(input())
draw  = []
for _ in range(lines):
    draw.append(input())

l = len(draw[-1])
d = set()

def res(x,y):
    while True:
        loc=draw[x][y]
        if y==l-2:
            a=draw[x][y+1]
            d.add(a)
            return a
        if loc=="|":
            x+=1
            continue
        if loc=="'":
            y+=1
            continue
        if loc=="+":
            return "not("+res(x,y+1)+")"
        if x+1<lines and draw[x+1][y] in "|'":
            return "not("+res(x+1,y)+") or ("+res(x,y+1)+")"
        y+=1

tmp     = res(0,0)
d       = "".join(sorted(d))
cas     = []

for l in product((False,True),repeat=len(d)):
    temp=tmp
    for i in range(len(d)):
        temp=temp.replace(d[i],str(l[i]))
    if not eval(temp):
        cas.append(l)
if cas:
    for l in cas:
        ch=[]
        for i in range(len(d)):
            ch+=[d[i],str(l[i])]
        print(" ".join(ch))
else:
    print("TAUTOLOGY")
