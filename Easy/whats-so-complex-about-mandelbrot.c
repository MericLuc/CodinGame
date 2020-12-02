#include <stdio.h>

main() {
    double _a,_b; scanf("%lf %lfi\n",&_a,&_b);
    int     m;    scanf("%d", &m);

    double ra=0, rb=0;  
    for (int n = 1 ; n < m ; n++) {
        double tmp = rb*rb;
        rb  = 2*ra*rb   + _b;
        ra  = ra*ra-tmp + _a;
        if ( (ra*ra + rb*rb) > 4.0) { m = n; break; }
    }
    printf("%d\n",m);
}