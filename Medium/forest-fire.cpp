#include <bits/stdc++.h>

using namespace std;

int m[20][20];

template<typename F>
inline void FOR(bool& pred1, bool pred2, int XMin, int XMax, int YMin, int YMax, F f) {
    if ( pred2 )
        for     (int i = XMin; i < XMax; ++i )
            for (int j = YMin; j < YMax; ++j ) if ( pred1 ) { f(i, j); }
}

int check( int I, int J, int c ) {
    int l_res(0);
    bool p(true);
    FOR( p, true, I, I+c+1, J, J+c+1, [&l_res](int i, int j){ l_res += m[i][j]; } );
    return l_res;
}

int main() {
    int L, water, N, x, y;
    cin >> L >> water; cin.ignore();

    while ( cin >> N )
    {
        bool d(true);
        for     (int i = 0; i < 20; ++i )
            for (int j = 0; j < 20; ++j ) m[i][j] = 0;

        for ( int i = 0; i < N && (cin >> x >> y); i++ ) { m[x][y] = 1; }

        for ( int nC = 9; (nC > 0) && d; nC-- )
        {
            FOR(d, N>=6 && nC >=6, 0, L-2, 0, L-2, [&](int i, int j) {
                if ( check( i, j, 2 ) == nC ) { d=false; water -=2100; printf("C %d %d\n", i, j); }} );
        }

        for ( int nC = 9; (nC > 0) && d; nC-- )
        {
            FOR(d, N>=4 && nC >=3, 0, L-1, 0, L-1, [&](int i, int j) {
                if ( check( i, j, 1 ) == nC ) { d=false; water -=1200; printf("H %d %d\n", i, j); }} );
        }

        for ( int nC = 9; (nC > 0) && d; nC-- )
        {
            FOR(d, N   , 0, L  , 0, L  , [&](int i, int j) {
                if ( m[i][j] ) { d=false; water -=600; printf("J %d %d\n", i, j); }} );  
        }  
    }
}