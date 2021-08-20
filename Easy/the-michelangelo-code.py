w = ''.join(i.lower() for i in input() if i.isalpha())
for i in  sorted([input() for i in range(int(input()))], key=lambda x: len(x), reverse=True):
    cpy = w
    for j in range(w.count(i[0])):
        s = cpy.index(i[0])
        for n in range(2, len(cpy)):
            if cpy[s:s + len(i) * n:n] == i:
                x = cpy[s:s + len(i) * n - n + 1]
                print(''.join(x[k].upper() if x[k] in i and k % n == 0 else x[k] for k in range(len(x))))
                exit()
        cpy = cpy[s+1:]