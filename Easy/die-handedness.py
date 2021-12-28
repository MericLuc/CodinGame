key  = int(input().strip())
vals = { 1: '23', 2: '31', 3: '12', 4: '21', 5: '13', 6: '32' }
str  = input()
s    = [int(i) for i in str]

print('degenerate' if s[0]+s[2] != 7 or s[1]+s[3] != 7 else 'right-handed' if vals[key] in str*2 else 'left-handed')
