import sys
import math
player =["a","b","c","d","e","f","g","h","i","j","k"]
vitesse=list()
virage =list()
mini   =list()
rank   =list()
n      = int(input())
v      = int(input())

for i in range(n):
    speed = int(input())
    vitesse.append(speed)
    
for i in range(v):
    bends = int(input())
    virage.append(bends)

for r in virage:
    for a in range(56):
        v=55-a
        if 90-math.degrees(math.atan((v**2)/(r*9.81)))>30:
                mini.append(v)
                break
mini.sort()
print(mini[0])
place=0
for e in vitesse:
    nb=chute=0
    for r in virage:
        nb+=1
        if 90-math.degrees(math.atan((e**2)/(r*9.81)))<=30:
            rank.append((nb,e,player[place]))
            chute=1
            break
    if chute==1:
        chute=0
    else:
        rank.append((999,e,player[place]))
    place+=1
rank.sort(reverse=True)
print("y")
for e in rank:
    x,y,z=e
    print(z)