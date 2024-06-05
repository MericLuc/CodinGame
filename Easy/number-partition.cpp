#include <bits/stdc++.h>

void P(int N, int k, std::deque<int> cP) noexcept {
    if ( 0 == N ) {
        std::stringstream ss;
        std::string       res;
        for ( const auto& elm : cP ) { ss << elm << ' '; }
        res = ss.str();
        res.pop_back();
        std::cout << res << std::endl;
    }
    else {
        for ( int i{ k }; i > 0; i-- ) {
            auto cPP{ cP };
            cPP.push_back( i );
            P(N - i, std::min(N - i, i), cPP ); 
        }
    }
}

int main() {
    int n;
    std::cin >> n; std::cin.ignore();

    P(n, n, {});
}