class Tribute():
    def __init__(self, name):
        self.name   = name
        self.killed = []
        self.killer = None
    def setKill  (self, name):   self.killed.append(name)
    def setKiller(self, name): self.killer = name
    def getMesg  (self):
        killed = "None" if len(self.killed) == 0 else ", ".join(sorted(self.killed))
        killer = "Winner" if self.killer is None else self.killer
        return "Name: {}\nKilled: {}\nKiller: {}".format(self.name, killed, killer)

tribes = int(input())
plrs   = dict()
for i in range(tribes):
    pName       = input()
    plrs[pName] = Tribute(pName)
for i in range(int(input())):
    s = input().split(" killed ")
    for victim in s[1].split(", "):
        plrs[s[0]  ].setKill  (victim)
        plrs[victim].setKiller(s[0])

print("\n\n".join([plrs[k].getMesg() for k in sorted(plrs.keys())]))
