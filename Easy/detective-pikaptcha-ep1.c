#include <stdlib.h>
#include <stdio.h>
#include <string.h>

main()
{
    int  w, h;  scanf("%d%d", &w, &h);
    char line[101][101];
   
    for     (int i = 0; i < h; i++) {scanf("%s", line[i]); }
    for     (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (line[i][j] != '#')  {
                if( i > 0   && line[i-1][j  ] != '#' ) { line[i][j]++; }
                if( i < h-1 && line[i+1][j  ] != '#' ) { line[i][j]++; }
                if( j > 0   && line[i  ][j-1] != '#' ) { line[i][j]++; }
                if( j < w-1 && line[i  ][j+1] != '#' ) { line[i][j]++; }
            }
        }
        printf("%s\n", line[i]);
    }
}