#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int I[100][100];  // Input image      - grayscale
int E[100][100];  // energy image     - energy of each pixels
int C[100][100];  // Cumulative image - Cumulative energy of each pixels
int H, W, V, max, res, n;

#define MIN(a,b) ( ( (a) < (b) ) ? (a) : (b) )
#define FOR_IMAGE(a) for(int i=0; i<H; i++){for(int j=0; j<W; j++){a;}}
#define PRINT_IMAGE(a) ({\
    for(int i=0; i<H; i++){\
        for(int j=0; j<W; j++){ fprintf(stderr, "%3d ", a[i][j]); }\
        fprintf(stderr, "\n");\
    }\
    })

void px_energy( int i, int j ) { 
    E[i][j] = 0;
    if ( i > 0 && i < H-1 ) { E[i][j] += abs( I[i+1][j  ] - I[i-1][j  ] ); }
    if ( j > 0 && j < W-1 ) { E[i][j] += abs( I[i  ][j+1] - I[i  ][j-1] ); }
}

void px_cumul( int i, int j ) { 
    C[i][j] = E[i][j];
    if ( i > 0 ) { 
        int l = ( j == 0   ) ? 1e8 : C[i-1][j-1];
        int r = ( j == W-1 ) ? 1e8 : C[i-1][j+1];
        C[i][j] += MIN ( MIN( l , C[i-1][j] ), r ); 
    }
}

void update() {
    int l_min = 1e8; int l_j; 
    for(int j=0; j<W; j++) 
            if ( C[H-1][j] < l_min )  { res = C[H-1][j]; l_min = res; l_j = j; }
    for ( int j = l_j; j < W-1; j++ ) { I[H-1][j] = I[H-1][j+1];               }
    for(int i=H-2; i>=0; i--) {
        l_min = 1e8;
        int j_min = (l_j-1<0  ) ? 0  : l_j-1; 
        int j_max = (l_j+1>W-1) ? W-1: l_j+1;
        for(int j= j_min; j <= j_max; j++) {
            if ( C[i][j] < l_min ) { l_min = C[i][j]; l_j = j; }
        }
        for ( int j = l_j; j < W-1; j++ ) { I[i][j] = I[i][j+1]; }
    }
    memset(E, 0, sizeof(E[0][0]) * 10000);
    memset(C, 0, sizeof(C[0][0]) * 10000);
}

main() {
    char magic[4], comment[2]; 
    scanf("%s%d%d%s%d%d", magic, &W, &H, comment, &V, &max);
    n = W-V;
    
    FOR_IMAGE(scanf("%d", &I[i][j]););
    for (int cmpt = 0; cmpt < n; cmpt++) {
        FOR_IMAGE(px_energy( i, j); );
        FOR_IMAGE(px_cumul ( i, j); );
        update();
        printf("%d\n",res);
        W--;
    }
}