#include <stdio.h>
#include <stdbool.h>

int gcd(int i1, int i2) {
    if( i1 < i2     ) return gcd(i2, i1);
    if( i1 % i2 == 0) return i2;
    return gcd( i2, i1%i2);
}

int pw(int i1, int i2, int mod) {
    if ( i2 == 0   ) return 1; 
    long t = pw(i1, i2/2, mod) % mod; 
    t      = (t * t) % mod; 
    if (i2 % 2 == 1) { t = (t * i1) % mod; }
    return t; 
}

bool check(int n) { 
    bool prime = true;
    for (int a = 2; a < n; a++)
        if (gcd(n, a) == 1) {
            if (pw(a, n, n) != a)   { return false;  }
        } else                      { prime = false; }
    return !prime; 
} 

main() {
    int n; scanf("%d", &n);
    printf("%s\n", check(n)?"YES":"NO");
}