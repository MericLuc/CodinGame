#include <stdio.h>

main() {
    int N, fl = 1, tmp = 0; scanf("%d", &N);
    char pd[1000], * pt[] = { " *** ",
                              " * * ",
                              " * * ",
                              "*****" };
    
    while( (tmp += fl) <= N ) { fl++; } --fl;
    
    for     ( int i = 1; i <= fl;      i++ )
        for ( int j = 0; j < 4;        j++ ) {
            memset(pd, ' ', (fl - i)*3); pd[(fl - i)*3] = 0;
            printf("%s", pd);
            for     ( int t = 0; t < i; t++ ) {
                printf("%s", pt[j]); 
                if( t < i -1 ) { putchar(' '); }
            }
            printf("%s\n", pd);
        }
}