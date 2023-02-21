#include <bits/stdc++.h>

struct Snail { int num, x, y; float speed; };

int main()
{
    int nb, w, h; std::cin >> nb; std::cin.ignore();
    std::vector<Snail> snails(nb);
    for ( auto i{ 0 }; i < std::size(snails); ++i )
        snails[i].num = 1 + i, std::cin >> snails[i].speed, std::cin.ignore();

    std::cin >> h; std::cin.ignore(); 
    std::cin >> w; std::cin.ignore();
    std::vector<std::string> grid(h);
    for ( auto& line : grid ) { getline(std::cin, line); }

    std::vector<std::pair<int, int>> exits;
    for ( auto i{ 0 }; i < h; ++i )
        for ( auto j{ 0 }; j < w; ++j ) {
            switch ( grid[i][j] ) {
                case '#' : exits.push_back({i, j}); break;
                case '*' : break;
                default  : { 
                    auto& curSnail{ snails[ (grid[i][j] - '0') - 1 ] };
                    curSnail.x = i, curSnail.y = j;
                } break;
            }
        }

    int res, curT, minT{ std::numeric_limits<int>::max() };
    for        ( const auto& snail : snails ) {
        if     ( 0 == snail.speed ) continue;
        for    ( const auto& ex : exits ) {
            if ( auto curT{ ceil((abs(snail.x - ex.first) + 
                             abs(snail.y - ex.second))/snail.speed) }; curT < minT ) 
                res = snail.num, minT = curT;
        }
    }

    std::cout << res << '\n';
}