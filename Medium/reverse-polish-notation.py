INS = {'ADD': '+', 'SUB': '-', 'MUL': '*', 'DIV': '//', 'MOD': '%'}
n = int(input())
s = []
try:
    for i in input().split():
        if i in INS:
            a, b = s.pop(), s.pop()
            r = eval(b + INS[i] + a)
            s.append(str(r))
        elif i == 'POP':
            s.pop()
        elif i == 'DUP':
            s.append(s[-1])
        elif i == 'SWP':
            s[-1], s[-2] = s[-2], s[-1]
        elif i == 'ROL':
            s.pop()
            s[-3], s[-2], s[-1] = s[-2], s[-1], s[-3]
        else:
            s.append(i)
except:
    s.append('ERROR')
finally:
    print(' '.join(s))
