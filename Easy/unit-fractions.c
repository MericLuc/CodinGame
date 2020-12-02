#include <stdio.h>

main()
{
    long n, N; 
    scanf("%ld", &n);
    N = n*n;
    for( long i = 1; i < N/2+1; i++ )
    {
        long x = n+N/i, y = n+i;
        if ( x < y      ) { break;                                     }
        if ( N % i == 0 ) { printf("1/%ld = 1/%ld + 1/%d\n", n, x, y); }
    }
}