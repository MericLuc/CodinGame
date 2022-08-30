number = input()
D      = int(input())
ret    = 0

def DFS(nb, depth):
    global ret
    n = int(nb)
    if n % D == 0 and n > ret:
        ret = n
    if depth == 2:
        return    
    for i in range(len(number)-depth):
        DFS(nb[:i] + nb[i+1:], depth+1)    

DFS(number,0)
print(ret)