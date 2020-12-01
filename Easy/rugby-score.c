#include <stdio.h>

void main() {
    int N; scanf("%d", &N);
    for ( int tri = 0; tri*5 <= N; tri++ )
        for ( int transf = 0; (transf <= tri) && (transf*2 <= N - tri * 5); ++transf )
            if ( ( (N - tri * 5 - transf * 2) % 3) == 0 ) 
                printf("%d %d %d\n", tri, transf, (N - tri * 5 - transf * 2) / 3);
}