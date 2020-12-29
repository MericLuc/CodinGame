input()
IN = list( map( int, input().split() ) )
h, ret = max( IN ), []

for c in IN:
    ret.extend(' ' * (h-i-1) + '/'  + ' ' * i for i in range( c ) )
    ret.extend(' ' * (h-i-1) + '\\' + ' ' * i for i in range( c-1, -1, -1) )
for s in zip(*ret):
    print( ''.join(s).rstrip() )