#include <bits/stdc++.h>

using Grid = std::vector< std::string >;

const auto printGrid = [](const Grid& g, std::ostream& os = std::cout) {
    std::for_each( std::begin(g), std::end(g), [&os](const auto& line) {
        os << line << "\n";
    }); 
};

const auto neighbours = [](const Grid& g, int x, int y) {
    std::vector< std::pair<int, int> > ret{};
    for ( int di = -1; di <= 1; ++di )
        for ( int dj = -1; dj <= 1; ++dj )
            if ( di || dj ) {
                int i{ x + di }, j{ y + dj }; 
                if ( i >= 0 && i < g.size() && j >= 0 && j < g[0].size() ) 
                    ret.emplace_back(i,j);
            }
    return ret;
};

int main()
{
    int w, h; std::cin >> w >> h; std::cin.ignore();

    Grid g(h, "");
    for (auto& line : g )
        getline(std::cin, line);
    
    for( int i = 0; i < h; ++i )
        for ( int j = 0; j < w; ++j )
            if ( g[i][j] != 'x' )
                g[i][j] = '0' + [&g, n = neighbours(g, i, j)]() {
                    int ret{ 0 };
                    std::for_each( std::begin(n), std::end(n), [&g, &ret](auto&& nn){
                        if ( g[nn.first][nn.second] == 'x' ) ++ret;
                    });
                    return ret;
                }();
    
    for( int i = 0; i < h; ++i )
        for ( int j = 0; j < w; ++j )
            g[i][j] = ( g[i][j] == 'x' ) ? '.' : ( ( g[i][j] == '0' ) ? '.': g[i][j]);

    printGrid(g, std::cout);
}
