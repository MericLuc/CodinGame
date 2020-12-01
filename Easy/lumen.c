#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int N, L;

int getBlackSpots( const int array[][N] )
{
    int l_return = 0;
    
    for( int i = 0; i < N; i++ )
        for( int j = 0; j < N; j++ )
            l_return += ( array[i][j] == 0 ) ? 1 : 0;
    
    return l_return;
}

int updateOne( const int x1, const int x2, const int y1, const int y2)
{
    int l_return = L;
    l_return -= ( abs(x2-x1) > abs(y2-y1) ) ? abs(x2-x1) : abs(y2-y1);
    
    return ( l_return > 0 ) ? l_return : 0;
}

void update( const int row, const int col, int array[][N])
{
    for( int i = 0; i < N; i++ )
        for( int j = 0; j < N; j++ ) {
            int l_tmp = updateOne(row, i, col, j);
            array[i][j] = (l_tmp > array[i][j]) ? l_tmp : array[i][j];
        }
}

void main()
{
    scanf("%d%d", &N, &L); fgetc(stdin);
    int square[N][N]; memset( square, 0, N * N * sizeof(int) );

    for ( int i = 0; i < N; i++ ) {
        char LINE[501]; fgets(LINE, 501, stdin);
        for ( int j = 0; j < strlen(LINE); ++j ) if ( LINE[j] == 'C' ) update ( i, j/2, square );
    }

    printf("%d\n", getBlackSpots(square) );
}