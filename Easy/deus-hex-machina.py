# Based on MJZ solution

n = input()
b = bin(int(n, 16))[2:]
if b.count('0') % 2: n = n.translate(str.maketrans("2345679abcdef", "5##2a#e6d#b9#"))[::-1]
if b.count('1') % 2: n = n.translate(str.maketrans("2345679abcdef", "53#2e#a9#c#6#"))

print('Not a number' if '#' in n else n[:1000])