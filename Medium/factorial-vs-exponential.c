#include <stdio.h>
#include <math.h>
main() {
    int K; scanf("%d", &K);
    for (int i = 0; i < K; i++) {
         int n = 0; float a; double f = 0; 
         scanf("%f", &a); a = log10(a);
         while(1) {
             f += log10(++n); 
             if( f > a*n ) { printf("%d%s", n, (i==K-1)?"":" "); break; }
         }
    }
}