#include <stdio.h>
#define _IT(a,b) for (int i = 1; i <= M; i++) { for (int j = 1; j <= N; j++) a; b; }

int M, N, r = 0, s[101][101];

void paths(int p_i, int p_j ) { 
    if ( p_i== M && p_j == N            ) { r++; return;         }
    if ( p_i < M && s[p_i+1][p_j  ] == 0) { paths(p_i+1, p_j  ); }
    if ( p_j < N && s[p_i  ][p_j+1] == 0) { paths(p_i  , p_j+1); }
} 

main() {
    scanf("%d%d", &M, &N); fgetc(stdin);
    _IT(s[i][j]  = fgetc(stdin) - '0', fgetc(stdin));
    paths(1,1);
    printf("%d\n", r);
}