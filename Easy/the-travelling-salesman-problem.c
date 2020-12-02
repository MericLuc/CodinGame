#include <stdio.h>
#include <math.h>
#include <string.h>

typedef struct _Pt { int x, y; } Pt;

float d( Pt* p1, Pt* p2) {
    float tx = p1->x - p2->x, ty = p1->y - p2->y;
    return sqrt(tx*tx + ty*ty); 
}

main() {
    int   N; scanf("%d", &N);
    float res = 0.f;
    Pt    c[N], init;
    for (int i = 0; i < N; i++) { scanf("%d%d", &c[i].x, &c[i].y); }
    init = c[0];
    
    while(N > 1) {
        float minD = 1e9; int minIdx = 0;
        for (int i = 1; i < N; i++) {
            float tmp_d =  d(c, c+i);
            if ( tmp_d< minD ) { minD = tmp_d; minIdx = i; }
        }
        res += minD;
        c[0] = c[minIdx];
        memmove( c+minIdx, c+minIdx+1, (N-1-minIdx)*sizeof(Pt) );
        N--;
    }
    printf("%d\n", (int)round(res + d(&init, &c[0])) );
}