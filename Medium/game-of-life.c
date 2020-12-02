#include <stdio.h>

char t[100+2][100+2];

main() {
    int width,height;
    scanf("%d%d\n", &width, &height);
    
    for (int l = 1; l <= height; l++) {
        for (int c = 1; c <= width ; c++) {
            t[l][c] = getchar() - '0';
        }
        getchar();
    }
    for (int l = 1; l <= height; l++) {
        for (int c = 1 ; c <= width ; c++) {
            int count = t[l-1][c-1] + t[l-1][c]  + t[l-1][c+1]
                      + t[l  ][c-1]              + t[l  ][c+1]
                      + t[l+1][c-1] + t[l+1][c]  + t[l+1][c+1];
            int x;
            if      (count == 2) x = t[l][c];
            else if (count == 3) x = 1 ;
            else                 x = 0;
            putchar('0' + x);
        }
        putchar('\n');
    }
}