class Sol:
    def __init__(self, name, parent, birth, death, religion, gender):
        self.name     = name
        self.parent   = parent
        self.birth    = int(birth)
        self.death    = int(death) if death != '-' else None
        self.religion = religion
        self.isfemale = gender == 'F'
        self.children = []

    def addChild(self, child):
        if child.parent == self.name: self.children += [child]
        else:
            for i in self.children:   i.addChild(child)
    
    def traverse(self):
        succession = []
        if not self.death and self.religion == 'Anglican': succession += [self]
        sortedChildren = sorted(self.children, key=lambda child: (child.isfemale, child.birth))
        for child in sortedChildren: succession += child.traverse()
        return succession

n = int(input())
succ = Sol(*input().split())
    
for i in range(n - 1):
    i = Sol(*input().split())
    succ.addChild(i)

for i in succ.traverse():
    print(i.name)