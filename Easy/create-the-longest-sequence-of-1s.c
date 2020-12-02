#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char b[1000];

bool stop  (int pos) { return ( (pos >= strlen(b) || pos < 0) || (b[pos] == '0') ); }
int  seq   (int pos) { return (1 + left(pos-1) + right(pos+1)  ); }
int  left  (int p)   { return ( stop(p) ? 0 : (1 + left (p-1)) ); }
int  right (int p)   { return ( stop(p) ? 0 : (1 + right(p+1)) ); }

main()
{
    fgets(b, 1000, stdin);
    int  l_tmp = 0, l_res = 1;
    char l_swap;
        
    for ( int i = 0; i < strlen(b); i++ )
    {
        l_swap = b[i];
        b[i]   = '1';
        l_tmp  = seq(i);
        b[i]   = l_swap;
        if ( l_tmp > l_res ) { l_res = l_tmp; }
    }
    printf("%d\n", l_res);
}