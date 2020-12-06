#include <stdio.h>

#define MIN(a,b)((a<b)?a:b)
#define MAX(a,b)((a<b)?b:a)

typedef struct _Pt { int x, y; } Pt;

int N, x, y, x_min = 0, x_max = 0, y_min=0, y_max=0;
Pt  pts[42];

int find_pt( int x, int y ) {
    for ( int i = 0; i < N; i++ ) { if ( pts[i].x == x && pts[i].y == y ) { return 1; } }
    return 0;
}

main() {
    scanf("%d", &N);
    for (int i = 0; i < N &&  scanf("%d%d", &x, &y); i++) { 
        pts[i] = (Pt) {x, y};
        x_min = MIN(x_min, x); x_max = MAX(x_max, x);
        y_min = MIN(y_min, y); y_max = MAX(y_max, y);
    }
    x_min --; x_max ++;
    y_min --; y_max ++;
    
    for     ( int i = y_max; i >= y_min; i-- ) {
        for ( int j = x_min; j <= x_max; j++ ) {
            char curr = '.';
            if      ( i == 0 && j == 0 ) { curr = '+'; }
            else if ( i == 0           ) { curr = '-'; }
            else if (           j == 0 ) { curr = '|'; }
            
            if ( find_pt(j,i) == 1 )     { curr = '*'; }
            putchar(curr);
        }
        printf("\n");
    }
}