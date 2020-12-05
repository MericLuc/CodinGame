#include <stdlib.h>
#include <stdio.h>

char a[21][22];
int X, Y, W, H, nRes = 0;

typedef struct { int x,y; } pt;
pt pRes[100];

void check(int x, int y) {
    if ( a[y][x] == '.' ) {
        a[y][x]   = 'X';
        if (x==0 || y==0 || x==W-1 || y==H-1) { pRes[nRes].x=x; pRes[nRes++].y=y; return; }
        if ( y+1 <  H) check(x   , y+1);
        if ( y-1 >= 0) check(x   , y-1);
        if ( x+1 <  W) check(x+1 , y  );
        if ( x-1 >= 0) check(x-1 , y  );
    }
}

int cmp( const pt * a, const pt *b) {
    if (a->x != b->x) return a->x - b->x;
                      return a->y - b->y;
}

main() {
    scanf("%d%d%d%d", &W, &H, &X, &Y);
    for (int y = 0; y < H; y++) { scanf("%s",a+y); }
    check(X,Y);
    qsort(pRes, nRes, sizeof(pt), cmp);
    printf("%d\n", nRes);
    for (int i= 0; i < nRes; i++) { printf("%d %d\n", pRes[i].x,pRes[i].y); }
}