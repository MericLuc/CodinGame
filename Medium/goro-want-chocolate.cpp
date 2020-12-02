#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int res[150][150] = {0}; 
  
int computeMin (int h, int w) { 
    int v_min   = 150; int h_min   = 150; 
    if ( h == w    ) return 1; 
    if ( res[h][w] ) return res[h][w]; 
      
    for ( int i = 1; i<= h/2; i++ ) {
        int tmp = computeMin(i, w) +  computeMin(h-i, w);
        h_min   = (tmp < h_min) ? tmp : h_min;
    }
      
    for ( int i = 1; i <= w/2; i++ ) { 
        int tmp = computeMin(h, i) +  computeMin(h, w-i);
        v_min   = (tmp < v_min) ? tmp : v_min;
    } 

    res[h][w] = (h_min < v_min) ? h_min : v_min;  
    res[w][h] = res[h][w];
    return res[h][w]; 
} 

main() {
    int h, w; 
    scanf("%d%d", &h, &w);
    printf("%d\n", computeMin(h, w) );
}