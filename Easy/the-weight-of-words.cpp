#include <bits/stdc++.h>

int main()
{
    int steps, h, w;
    std::cin >> steps >> h >> w; std::cin.ignore();

    std::vector<std::string> grid(h);
    std::vector<size_t>      wrows(h, 0), wcols(w, 0);
    
    const auto& computeRowsWeight{ [&](void) -> void {
        for ( auto r{ 0 }; r < h; ++r )
            wrows[r] = std::accumulate(std::cbegin(grid[r]), std::cend(grid[r]), 0);
    } };

    const auto& computeColsWeight{ [&](void) -> void {
        for ( auto c{ 0 }; c < w; ++c ) {
            wcols[c] = 0;
            std::for_each(std::cbegin(grid), std::cend(grid), 
                        [&](const auto& line){ wcols[c] += line.at(c); });
        }
    } };

    const auto& performRowsSwap{ [&](void) -> void {
        for ( auto r{ 0 }; r < h; ++r ) {
            auto&       curW{ wrows.at(r) };
            std::string tmp(w, ' ');

            for ( auto c{ 0 }; c < w; ++c )
                tmp[(c + curW) % w] = grid[r][c];

            for ( auto c{ 0 }; c < w; ++c )
                grid[r][c] = tmp[c];
        }
    }};

    const auto& performColsSwap{ [&](void) -> void {
        for ( auto c{ 0 }; c < w; ++c ) {
            auto&       curW{ wcols.at(c) };
            std::string tmp(h, ' ');

            for ( auto r{ 0 }; r < h; ++r )
                tmp[(r + curW) % h] = grid[r][c];

            for ( auto r{ 0 }; r < h; ++r )
                grid[r][c] = tmp[r];
        }
    }};

    for (int i{ 0 }; i < h; ++i)
        getline(std::cin, grid[i]);

    while ( steps-- ) {
        computeColsWeight();
        performColsSwap();

        computeRowsWeight();
        performRowsSwap();
    }

    for (const auto& line : grid )
        std::cout << line << std::endl;
}