#include <bits/stdc++.h>

int main()
{
    int n, cmpt{0}, sq;
    std::cin >> n; std::cin.ignore();
    
    for ( int b = 0, sq = std::floor( std::sqrt(n) ); b <= sq; ++b ) 
        for ( int c = 0; c <= sq; ++c )
            for ( int d = 0; d <= sq; ++d ) {
                int tmp(n-(b*b + c*c + d*d));
                if ( tmp < 0 ) break;
                double a( std::sqrt(tmp) ), e(std::sqrt(b+3*c+5*d));
                if ( std::floor(a) == a && std::floor(e) == e ) ++cmpt;
            }

    std::cout << cmpt << "\n";
}