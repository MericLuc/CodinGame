#include <stdlib.h>
#include <stdio.h>

struct horse {
    int v, e;
};

int d( const struct horse* h1, const struct horse* h2) { 
    return ( (h1 == h2) ? 10e9 : abs(h2->v - h1->v) + abs(h2->e - h1->e) ); 
}

main() {
    int          N, V, E; scanf("%d", &N);
    int          min_d = 10e9;
    struct horse h[N], *p = h;
    for (int i = 0; i < N; i++) { scanf("%d%d", &p->v, &p->e); p++; }
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) 
            min_d = (d(&h[i], &h[j]) < min_d) ? d(&h[i], &h[j]) : min_d;
    printf("%d\n", min_d);
}