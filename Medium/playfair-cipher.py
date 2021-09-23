keys = [input().split() for _ in range(5)]
dic  = dict((keys[y][x], (x, y)) for x in range(5) for y in range(5))
dm   = 1 if input() == 'ENCRYPT' else -1

for _ in range(int(input())):
    msg = [a for a in input().upper() if a in dic]
    if len(msg) % 2 == 1: 
        print('DUD')
    else:
        for i in range(len(msg)//2):
            x1, y1 = dic[msg[2*i  ]]
            x2, y2 = dic[msg[2*i+1]]
            if   y1 == y2:
                x1, x2 = (x1 + dm) % 5, (x2 + dm) % 5
            elif x1 == x2:
                y1, y2 = (y1 + dm) % 5, (y2 + dm) % 5
            else:
                x1, x2 = x2, x1
            print(keys[y1][x1], keys[y2][x2], sep='', end='')
        print()
