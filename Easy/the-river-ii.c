#include <stdio.h>

long r1;
char tested[100000] = {0};

void next(long* x) {
    long l_tmp = *x;
    while (l_tmp) { *x += l_tmp %10; l_tmp /= 10; }
    tested[*x] = 1;
}

int testFlow(long i) {
    while ( i < r1 && (tested[i] == 0) ) { next(&i); if ( i == r1) return 1; }
    return 0;
}

void main() {
    scanf("%lld", &r1);
    for ( long i = r1 - 1; i > 0; --i ) if ( testFlow(i) ){ printf("YES\n"); return; }
    printf("NO\n");
}