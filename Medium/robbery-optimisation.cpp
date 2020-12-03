#include <stdio.h>

#define MAX(a,b) (((a) > (b))?(a):(b))
int       N;
long long h  [101], res[101];

long long a( int i ) {
    if ( i >= N      ) { return 0;                                                       }
    if ( res[i] == 0 ) { long long r1 = h[i] + a(i+2), r2 = a(i+1); res[i] = MAX(r1,r2); }
    return res[i];
}

main() {
    scanf("%d", &N);
    for (int i = 0; i < N  ; i++) { scanf("%lld", &h[i]); fprintf(stderr, "%lld ", h[i]); }
    printf("%lld\n", a(0) );
}