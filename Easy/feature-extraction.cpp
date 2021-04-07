#include <bits/stdc++.h>

template < typename T >
using V = std::vector<T>;

int convAt( const V< V<int> >& img, 
            const V< V<int> >& krnl, 
            const std::pair<int, int>& pos)  {
    int ret{0};

    for ( int i = 0; i < std::size(krnl[0]); ++i ) {
        for ( int j = 0; j < std::size(krnl); ++j ) {
            ret += img[i + pos.first][j + pos.second] * krnl[i][j]; 
        }
    }

    return ret;
}

int main()
{
    int r, c, m, n;
    std::cin >> r >> c; std::cin.ignore();

    V< V<int> > img(r, V<int>(c,0) );
    for ( int i = 0; i < r; ++i )
        for ( int j = 0; j < c; ++j ) { std::cin >> img[i][j]; std::cin.ignore(); }

    std::cin >> m >> n; std::cin.ignore();
    V< V<int> > krnl(m, V<int>(n,0) );
    for ( int i = 0; i < m; ++i )
        for ( int j = 0; j < n; ++j ) { std::cin >> krnl[i][j]; std::cin.ignore(); }

    V< V<int> > res(r - m, V<int>(c - n, 0) );
    for ( int i = 0; i <= r - m; ++i ) {
        std::string ss;
        for ( int j = 0; j <= c - n; ++j )
            ss += std::to_string(convAt(img, krnl, {i, j})) + " "; 
        ss.pop_back(); 
        std::cout << ss << std::endl;
    }
}
