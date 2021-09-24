from collections import defaultdict

n, m  = [int(i) for i in input().split()]
inStr = ''.join(input() for i in range(n))

nt = list('ZYXWVUTSRQPONMLKJIHGFEDCBA')
freqs = defaultdict(list)
rules = []

while True:
    freqs.clear()
    for i in range(len(inStr) - 1):
        key = inStr[i : i + 2]
        if i and freqs[key] and freqs[key][-1] >= i - 1:
            continue
        freqs[key].append(i)
    
    dom = max(freqs, key=lambda p: len(freqs[p]))
    if len(freqs[dom]) == 1:
        break
    
    t = nt.pop(0)
    inStr = inStr.replace(dom, t)
    rules.append((t, dom))

print(inStr)
for rule in rules:
    print("{} = {}".format(*rule))