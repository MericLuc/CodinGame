#include <stdio.h>

main() {
    int N, c[1500]; scanf("%d", &N);
    for (int i = 0; i < N; i++) { scanf("%d", &c[i]); }
    
    int idx = -1, sz = 0, st = 1e9;
    for (int i = 0; i < N-1; i++) {
        int l_idx = i, l_sz = 0, search = c[i]+1, l_st = c[i];
        for (int j = i+1; j < N; j++) if ( c[j] == search ) { search++; l_sz++; }
        if ( l_sz > sz || (l_sz == sz && l_st < st) ) {sz = l_sz; idx = l_idx; st = l_st; }
    }
    for(int i = 0; i < sz; i++) { printf("%d ", c[idx]+i); }
    printf("%d", c[idx]+sz);
}