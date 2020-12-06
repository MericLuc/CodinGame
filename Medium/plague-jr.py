from collections import deque

def simulate(node, edges, current_min):
    queue   = deque([(node, 0)])
    visited = {node}
    while queue:
        node, night = queue.popleft()
        if night >= current_min: return current_min
        for o in edges[node]:
            if o not in visited:
                queue.append((o, night + 1))
                visited.add(o)
    return night

def solution():
    num_rods = int(input())
    edges    = {}
    for _ in range(num_rods):
        a, b = map(int, input().split())
        if a not in edges: edges[a] = []
        if b not in edges: edges[b] = []
        edges[a].append(b)
        edges[b].append(a)

    current_min = float('inf')
    for node in edges:
        current_min = simulate(node, edges, current_min)
    print(current_min)

solution()
