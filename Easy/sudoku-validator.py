import sys

class Grid:
    def __init__(self, d): self.d = d
    def _row(self, i    ): return len(set(self.d[i])) == 9   
    def _col(self, j    ): return len(set([self.d[i][j] for i in range(9)])) == 9    
    def _sub(self, i, j ): return len(set([self.d[k][l] for k in range(i, i+3) for l in range(j, j+3)])) == 9    
    def _slv(self       ):
        for i in range(9):
            if not self._row(i) or not self._col(i): return False
        for i in (0, 3, 6):
            for j in (0, 3, 6):
                if not self._sub(i, j): return False
        return True
print(str(Grid([list(map(int, input().split())) for i in range(9)])._slv()).lower())