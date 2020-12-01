#include <stdio.h>

int  chess[8][8] = { 0 };
char rookPosition[3]; 
int  nbPieces;

void check_horizontal_left( int *index )  {
    *index = 0;
    for ( int h1 = 0; h1 < rookPosition[0] - 97; ++h1)
        if ( chess[rookPosition[1] - '0' -1][h1] > -1 ) *index = ( chess[rookPosition[1] - '0' -1][h1] == 0 ) ? h1 + 1 : h1;
}

void check_horizontal_right( int *index ) {
    *index = 7;
    for ( int h1 = rookPosition[0] - 97 +1; h1 < 8; ++h1)
        if ( chess[rookPosition[1] - '0' -1][h1] > -1 ) { *index = ( chess[rookPosition[1] - '0' -1][h1] == 0 ) ? h1 - 1 : h1; break; }
}

void check_vertical_bottom( int *index ) {
    *index = 0;
    for ( int h1 = 0; h1 < rookPosition[1] - '0' -1; ++h1) 
        if ( chess[h1][rookPosition[0] - 97] > -1 ) *index = ( chess[h1][rookPosition[0] - 97] == 0 ) ? h1 + 1 : h1;
}

void check_vertical_top( int *index )    {
    *index = 7;
    for ( int h1 =  rookPosition[1] - '0'; h1 < 8; ++h1)
        if ( chess[h1][rookPosition[0] - 97] > -1 ) { *index = ( chess[h1][rookPosition[0] - 97] == 0 ) ? h1 - 1 : h1; break; }
}

void main()
{
    int index = 0;
    for(int i = 0; i < 8; ++i) for(int j = 0; j < 8; ++j) chess[i][j] = -1;
    scanf("%s", rookPosition); scanf("%d", &nbPieces);
    fprintf(stderr, "rook Position %s\n", rookPosition);
    
    for (int i = 0; i < nbPieces; i++) {
        int colour; char onePiece[5];
        scanf("%d%s", &colour, onePiece);
        chess[onePiece[1] - '0' -1][onePiece[0] - 97] = colour;
    }
   
    int vals[2] = { -1, 1};
    char chars[3] = { '-', 'x'};
    for (int cmpt = 0; cmpt < 2; cmpt ++) {
        check_horizontal_left(&index);
        for ( int i = index; i < rookPosition[0] - 97; ++i )   
             if( chess[rookPosition[1] - '0' -1][i] == vals[cmpt]) printf("R%s%c%c%d\n", rookPosition, chars[cmpt], i + 97, rookPosition[1] - '0');
        
        check_vertical_bottom(&index);
        for ( int i =index; i < rookPosition[1] - '0'-1; ++i ) 
            if( chess[i][rookPosition[0] - 97] == vals[cmpt] ) printf("R%s%c%c%d\n", rookPosition, chars[cmpt], rookPosition[0], i+1); 
            
        check_vertical_top(&index);
        for ( int i = rookPosition[1] - '0'; i <= index; ++i ) 
            if( chess[i][rookPosition[0] - 97] == vals[cmpt] ) printf("R%s%c%c%d\n", rookPosition, chars[cmpt], rookPosition[0], i+1);

        check_horizontal_right(&index);
        for ( int i = rookPosition[0] - 96; i <= index; ++i )  
            if( chess[rookPosition[1] - '0' -1][i] == vals[cmpt] ) printf("R%s%c%c%d\n", rookPosition, chars[cmpt], i + 97, rookPosition[1] - '0');
    }
}