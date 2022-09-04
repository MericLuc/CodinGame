#include <bits/stdc++.h>

#define OUTS 38

int main() {
    std::mt19937  rand_gen(time(nullptr));
    int           m, n, totals(1e4), successes(0);
    
    std::cin >> m >> n;
    for   ( int i = 0; i < totals; ++i ) {
        std::set<int> results;
        for ( int j = 0; j < n; ++j )
            results.insert( rand_gen() % OUTS );
        if ( std::size(results) >= m ) ++successes;
    }
    
    std::cout << round( static_cast<double>(successes) / totals * 100 ) << "%";
}