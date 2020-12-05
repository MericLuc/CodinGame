#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int N, a[1000], res = 0, tmp_res = 0;

void check(int j, int d) {
    for(int i = j+1; i < N; i++) {
        int tmp = a[i]-a[j];
        if      ( tmp == d ) { tmp_res++; check(i, d); }
        else if ( tmp >  d ) { return;                 }
    }
}

void removeDuplicates() { 
    int temp[N], j = 0; 
    for (int i = 0; i< N-1; i++) if (a[i] != a[i+1]) { temp[j++] = a[i]; }
    temp[j++] = a[N-1]; 
    for (int i=0; i<j; i++) {a[i] = temp[i]; }
    N = j; 
}

main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) { scanf("%d", &a[i]); }
    removeDuplicates();
    for (int i = 0; i < N-1; i++) 
        for(int j = i+1; j < N; j++) {
            tmp_res = 2; check(j, a[j]-a[i]);
            if( tmp_res > res ) { res = tmp_res; }
        }
    printf("%d\n", res);
}