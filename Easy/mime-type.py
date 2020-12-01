import sys, math

N = int(input()) 
Q = int(input())
el=[]
ml=[]
found=0
for i in range(N):
    EXT, MT = input().split()
    el.append(EXT.lower())
    ml.append(MT)

for i in range(Q):
    fname = input() 
    ext   = fname.split(".")
    if("." in fname):
        if(ext[-1].lower() in el): print(ml[el.index(ext[-1].lower())])
        else:                      print("UNKNOWN")
    else:
        print("UNKNOWN")
