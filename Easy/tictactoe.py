from copy      import *
from itertools import *

################ FUNCTIONS ####################
def empty(g, x, y):
    return g[y][x] == "."

def is_O(g, x, y):
    return g[y][x] == "O"

def is_win(b):
    for x in range(3):
        ctest = True
        for y in range(3):
            ctest = ctest and is_O(b, x, y)
        if ctest:
            return True

    for y in range(3):
        ctest = True
        for x in range(3):
            ctest = ctest and is_O(b, x, y)
        if ctest:
            return True

    ctest = True
    for (x, y) in [(0, 0), (1, 1), (2, 2)]:
        ctest = ctest and is_O(b, x, y)
    if ctest:
        return True

    ctest = True
    for (x, y) in [(2, 0), (1, 1), (0, 2)]:
        ctest = ctest and is_O(b, x, y)
    return ctest

def show(b):
    print('\n'.join(l for l in b))

def cpy_with_move(g, x, y):
    g2    = copy(g)
    l2    = list(g2[y])
    l2[x] = "O"
    g2[y] = "".join(l2)
    return g2

################### MAIN #######################
g = []
for i in range(3):
    g.append(input())

for x,y in product(range(3), range(3)):
    if empty(g, x, y):
        g2 = cpy_with_move(g, x, y)
        if is_win(g2):
            show(g2)
            exit()
print("false")
