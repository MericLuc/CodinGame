#include <stdio.h>

main() {
    int n; long res = 0; scanf("%d", &n);
    for (int i = 1; i <= n; i++) { res+=(long)n/i*i; }
    printf("%ld\n", res);
}