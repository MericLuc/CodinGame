# Inspired from Carlwash's solution

def S(com):
    if not hasattr(S, "prio"):
     S.prio = dict(Pinned=2, Followed=1, none=0) 
    _, time, likes, pri = com[0].split('|')
    return S.prio[pri], int(likes), time

coms = []
for _ in range(int(input())):
    obj = input(), []
    if obj[0].startswith('    '):
        coms[-1][1].append(obj)
    else:
        coms.append(obj)

for c, reps in sorted(coms, key=S, reverse=True):
    print(c)
    for r, _ in sorted(reps, key=S, reverse=True):
        print(r)
