#include <bits/stdc++.h>

int main()
{
    int w, h, x, y, ret{0};
    std::cin >> w >> h >> x >> y; std::cin.ignore();

    std::vector< std::string > grid(h);
    for ( auto& line : grid ) { std::cin >> line; std::cin.ignore(); }

    auto it = [&](int& x, int& y) { 
        auto& val = grid[y][x];
        switch(val) {
            case '<': val = '^'; --y; break;
            case '>': val = 'v'; ++y; break;
            case 'v': val = '<'; --x; break;
            case '^': val = '>'; ++x; break;
            default: return false;
        }

        return x >= 0 && x < w && y >= 0 && y < h; 
    };

    int xi{x}, yi{y};
    while( ++ret )
        if ( !it(xi, yi) || ( xi == x && yi == y)) break;

    std::cout << ret << '\n';
}