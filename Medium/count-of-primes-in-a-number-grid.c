#include <stdio.h>

int R, C, res = 0;
long found[1000] = {0}, grid[8][8] = {0};

int find(long val) {
    for (int i = 0; i < res; i++) { if(found[i] == val){ return 1; } }
    return 0;
}

void check(int x, int y) {
    long val = grid[x][y]; prime(val);
    for(int i = x+1; i < R; i++ ) { val = 10*val + grid[i][y]; prime(val); }
    val     = grid[x][y];
    for(int i = y+1; i < C; i++ ) { val = 10*val + grid[x][i]; prime(val); }
}

void prime(long val) {
    int tmp = 1;
    if  (val < 2 || find(val) > 0        ) { return;                               }
    for (int i = 2; i <= sqrt(val);   i++) { if ( val%i == 0 ) { tmp = 0; break; } }
    if  (tmp == 1                        ) { found[res++] = val;                   }
}

main() {
    scanf("%d%d", &R, &C);
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++) { scanf("%d", &grid[i][j]); }

    for(int i = 0; i < R; i++)
        for (int j = 0; j < C; j++) { check(i,j); }
    printf("%d\n", res);
}