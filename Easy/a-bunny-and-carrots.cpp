#include <bits/stdc++.h>

int main()
{
    int m, n, t, col;
    std::cin >> m >> n >> t; std::cin.ignore();

    int ret =  2 * (m+n) ;
    std::vector<int> d(n + 2, 0);
    d[0] = d[n + 1] = m;

    int i = 0;
    while( std::cin >> col ) {
        ++d[col];

        ret += 2;
        if ( d[col - 1] >= d[col] ) ret -= 2; 
        if ( d[col + 1] >= d[col] ) ret -= 2;
        if ( d[col] == m          ) ret -= 2;

        std::cout << ret << "\n";
    }
}