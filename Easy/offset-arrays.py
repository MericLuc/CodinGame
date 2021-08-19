arrs = {}
for _ in range(int(input())):
    a,_,*v      = input().split()
    l           = a.find('[')
    s,e         = map(int,a[l+1:-1].split('..'))
    arrs[a[:l]] = dict(zip(range(s,e+1),map(int,v)))
*x,s = input().replace(']','').split('[')
s    = int(s)
for a in x[::-1]: s = arrs[a][s]
print(s)
