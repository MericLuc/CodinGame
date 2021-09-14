for _ in range( int(input())):
    i = int(input(), 2)
    if i == 0:
        print('0')
    else:
        i -= 1
        l = 1
        while i >= l * 2**(l-1):
            i -= l * 2**(l-1)
            l += 1
        n, i = divmod(i, l)
        n += 2**(l-1)
        print(f'{n:b}'[i])
