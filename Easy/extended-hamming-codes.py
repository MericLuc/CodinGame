data  = list(map(int, input()))
check = 0
for i in range(1,16):
    if data[i]: check ^= i
if check: data[check] ^= 1
print('TWO ERRORS' if sum(data)&1 else ''.join(map(str, data)))