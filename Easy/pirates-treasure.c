#include <stdio.h>

int W, H;
void check(int i, int j, int map[H][W]) {
    int indexes[5] = {i-1, i+1, j-1, j+1, 0};
    if ( map[i][j] != 0 ) return;
    if      ( i == H -1 ) { indexes[1] = i; ++indexes[4]; }
    else if ( i == 0    ) { indexes[0] = i; ++indexes[4]; }
    if      ( j == W -1 ) { indexes[3] = j; ++indexes[4]; }
    else if ( j == 0    ) { indexes[2] = j; ++indexes[4]; }
    
    int l_cmpt = 0;
    for (int c = indexes[0]; c <= indexes[1]; ++c) for (int d = indexes[2]; d <= indexes[3]; ++d) l_cmpt += map[c][d];
    if ( (l_cmpt == 8) || ( (l_cmpt == 5) && (indexes[4] == 1) ) || ( (l_cmpt == 3) && (indexes[4] == 2) ) ) printf("%d %d", j, i);
}

void main() {
    scanf("%d%d", &W, &H);
    int map[H][W];
    for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) scanf("%d", &map[i][j]);
    for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) check(i, j, map);
}