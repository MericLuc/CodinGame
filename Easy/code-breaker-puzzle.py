alpha = input()
msg   = input()
word  = input()
L     = len(alpha)

for a in range(L):
    for b in range(L):
        ret = ""
        for m in msg:
            ret += alpha[((alpha.find(m)+a)*b)%L]

        if word in ret:
            print(ret)
            exit(0)