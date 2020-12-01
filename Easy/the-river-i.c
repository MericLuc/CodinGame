#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void next(long long* x) {
    long long l_tmp = *x;
    while (l_tmp) { *x += l_tmp %10; l_tmp /= 10; }
}

void main() {
    long long r1, r2;
    scanf("%lld", &r1); scanf("%lld", &r2);
    while ( r1 != r2 ) ( r1 < r2 ) ?  next(&r1) : next(&r2);
    printf("%d\n", r1);
}