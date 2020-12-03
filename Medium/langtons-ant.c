#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _card { int x, y; } card;

main() {
    int  W, H, x, y, T; char d[2], C[31][31]; scanf("%d%d%d%d%s%d", &W, &H, &x, &y, &d, &T);
    int  dir_i; card dirs[4] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    switch(*d) {
        case 'N': dir_i = 0; break;
        case 'E': dir_i = 1; break;
        case 'S': dir_i = 2; break;
        case 'W': dir_i = 3; break;
    }
                        
    for (int i = 0; i < H; i++) { scanf("%s", C[i]);   }
    for (int i = 0; i < T; i++) {
        dir_i = (dir_i + 4 + (C[y][x] == '#' ? 1 : -1)) % 4;
        C[y][x] = (C[y][x] == '#' ? '.' : '#');
        x += dirs[dir_i].x; y += dirs[dir_i].y;
    }
    for (int i = 0; i < H; i++) { printf("%s\n", C[i]); }
}