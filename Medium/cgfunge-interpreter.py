# From User "MMMAAANNN"

DIR = (1, 0), (-1, 0), (0, 1), (0, -1)
out, direct, stack = '', DIR[0], []
x = y = smode = value = 0
grid = tuple(input() for i in range(int(input())))
while smode or value is not 'E':
    value, jump = grid[y][x], 1
    if value in '"':               smode  = not smode
    elif value.isdigit() or smode: stack += [(int, ord)[smode](value)]
    elif value in '+-*':           stack += [eval(str(stack.pop(-2)) + value + str(stack.pop()))]
    elif value in 'X':             stack += [stack.pop(), stack.pop()]
    elif value in 'D':             stack += [stack[-1]]
    elif value in 'P':             stack.pop()
    elif value in 'IC':            out   += (str, chr)[value is 'C'](stack.pop())
    elif value in '><v^':          direct = DIR['><v^'.index(value)]
    elif value in '_|':            direct = DIR[(value is '|') * 2 + bool(stack.pop())]
    elif value in 'S':             jump = 2
    x, y = x + direct[0] * jump, y + direct[1] * jump
print(out)
