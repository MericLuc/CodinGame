N = int(input())
B = input()
l = max(B.split('!'), key=len)
print(0 if B.index(l) == 0 else (N-1 if B.index(l) + len(l) == N else B.index(l) + len(l)//2))
