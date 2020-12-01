import re

cmpt = -1
def choiceReplace(match):
    global cmpt
    cmpt += 1
    l_tmp = match.group()[1:-1].split('|')
    return l_tmp[cmpt % len(l_tmp)]

N     = int(input())
lines = [''] * N

for i in range(N): lines[i] = input()
template = '\n'.join(lines)

out = re.sub('\([^)]*\)', choiceReplace, template)
print(out)
