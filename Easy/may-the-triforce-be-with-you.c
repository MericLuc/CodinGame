#include <stdlib.h>
#include <stdio.h>
#include <string.h>

main() {
    int N; scanf("%d", &N);
    char stars[500] = "*";
    
    for ( int i = 1; i <= N; i++ ) {        // top triangle
        printf("%c", (i == 1) ? '.' : ' ' );
        for (int j = 0; j < 2*N-1-i; j++)            { printf(" "); }
        printf("%s\n", stars);
        strcat(stars, "**");
    }
    strcpy(stars, "*");
    for (int i = 1; i <= N; i++) {          // bottom triangles
        for (int j = 1; j <= N-i; j++)               { printf(" "); }
        printf("%s", stars);
        for (int j = 1; j <= N*2-strlen(stars); j++) { printf(" "); }
        printf("%s\n", stars);
        strcat(stars, "**");
    }
}