import sys
import re

res = ":" + input()
zer = sorted(list(re.findall(":(?:0+:)+0+:",res)), key=lambda x:-1*len(x))
if (len(zer)) > 0:
    res = res.replace(zer[0],"::")
res = re.sub(":0+",":0",res)
res = re.sub(":0([1-9a-f])",":\\1",res)
res = re.sub("^:::","::",res)
res = re.sub("^:([^:])","\\1",res)
print(res)

# That would work too...
# import ipaddress
# print(ipaddress.IPv6Address(input()))
