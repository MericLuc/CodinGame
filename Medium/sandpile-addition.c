#include <stdio.h>
#include <string.h>

#define CELLS_IF for (int i = 1; i <= n; i++)for (int j = 1; j <= n; j++) 
#define CELLS_IT(a,b) for (int i = 1; i <= n; i++) { for (int j = 1; j <= n; j++) a; b; }

main() {
    int n, s[12][12], end;
    scanf("%d", &n); fgetc(stdin);
    
    CELLS_IT(s[i][j]  = fgetc(stdin) - '0', fgetc(stdin));
    CELLS_IT(s[i][j] += fgetc(stdin) - '0', fgetc(stdin));

    do {
        end = 1;
        CELLS_IF
            if ( s[i][j] > 3 ) {  s[i][j]-= 4; s[i-1][j]++; s[i+1][j]++;s[i][j-1]++;s[i][j+1]++; end = 0; }
    } while (end == 0);
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) printf("%d", s[i][j]);
        printf("\n");
    }
}