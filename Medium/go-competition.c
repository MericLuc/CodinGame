#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum colour {
    NO_COL  = 0,
    BLACK_R = 1,
    WHITE_R = 2,
    BOTH_R  = 3,
    HAS_ST  = 4,
    BLACK   = 5,
    WHITE   = 6
};

enum colour grid[ 400 ] = { 0 };
int L;

enum colour charToCol(char c) {
    switch (c) {
        case '.': return NO_COL;
        case 'B': return BLACK;
        case 'W': return WHITE;
    }
}

void fill_grid(void) {
    int ch;
    enum colour top, bot, lft, rht, acc;

    do { ch = 0;
        for     ( int i = 0; i < L; ++i ) {
            for ( int j = 0; j < L; ++j ) {

                if (grid[i*L+j] >= BOTH_R) continue;

                top    = (i == 0  ) ? NO_COL : grid[ (i-1) * L+j   ];
                lft    = (j == 0  ) ? NO_COL : grid[ i*L     + j-1 ];
                bot    = (i == L-1) ? NO_COL : grid[ (i+1)*L + j   ];
                rht    = (j == L-1) ? NO_COL : grid[ i*L     + j+1 ];
                acc    = grid[i*L+j] | top | bot | lft | rht;
                acc   &= ~HAS_ST;
                ch    |= grid[i*L+j] != acc;

                grid[i * L + j] = acc;
            }
        }
    } while (ch);
}

void compute_score(void) {
    int w = 6, b = 0;

    for (int i = 0; i < L*L; ++i) switch (grid[i] & ~HAS_ST) {
        case WHITE_R: ++w; break;
        case BLACK_R: ++b; break;
    }
    printf("BLACK : %d\nWHITE : %d.5\n%s WINS\n", b, w, (b>w)?"BLACK" : "WHITE");
}

main() {
    char ROW[1025];
    scanf("%d", &L); fgetc(stdin);
    
    for     (int i = 0; i < L && fgets(ROW, 1025, stdin); i++)
        for (int j = 0; j < L;                            j++) { grid[i*L+j] = charToCol(ROW[j]); }
        
    fill_grid();
    compute_score();
}