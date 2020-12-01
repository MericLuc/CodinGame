# Inspired by "Zexion" solution

from datetime import datetime as dt
b, e = [dt.strptime(input(), '%d.%m.%Y') for _ in range(2)]

d = (e - b).days
m = (dt.min + (e - b)).month - 1
y = d // 365

if y > 0: print('%d year%s, '  % (y, 's' if y > 1 else ''), end='')
if m > 0: print('%d month%s, ' % (m, 's' if m > 1 else ''), end='')
print('total %d days' % d)
