#include <bits/stdc++.h>

struct Pos { 
    int x, y; 
    friend bool operator<(const Pos& lhs, const Pos& rhs) noexcept {
        return lhs.x < rhs.x || ( (lhs.x == rhs.x) && (lhs.y < rhs.y) );
    }
};

struct Cell {
    char _val;
    bool _visited{ false };

    bool is_newland(void) const noexcept { return !_visited && _val == '#'; }
};

int main()
{
    size_t      N, cur, cmpt{ 0 };
    std::cin >> N;

    std::pair<size_t, size_t>       ret { 1, 0 };
    std::vector< std::vector<Cell>> grid{ N, {N, Cell() } };

    for     ( auto& line : grid )
        for ( auto& cell : line )
            std::cin >> cell._val;

    std::function<size_t(Pos, std::set<Pos>&)> process { 
        [&N, &grid, &cur, &process](Pos p, std::set<Pos>& vis) { 
        static const auto is_valid{ [&N]   (const Pos& p) { return p.x >= 0 && p.x < N && p.y >= 0 && p.y < N; } };
        static const auto is_vis  { [&grid](const Pos& p) { return grid[p.x][p.y]._visited; } };
        static const auto set_vis { [&grid](const Pos& p) { grid[p.x][p.y]._visited = true; } };
        static const auto is_water{ [&grid](const Pos& p) { return grid[p.x][p.y]._val == '~'; } };

        if ( is_valid(p) && !is_vis(p) && !is_water(p) ) {
            std::vector<Pos> neighs{ {p.x + 1, p.y    }, 
                                     {p.x - 1, p.y    }, 
                                     {p.x    , p.y + 1},
                                     {p.x    , p.y - 1} };
            
            std::for_each( std::begin(neighs), 
                           std::end(neighs), 
                           [&vis, &cur](const auto& pt) { 
                                if( is_valid(pt) && is_water(pt) && !vis.count(pt) ) { vis.insert(pt), ++cur; } } );

            set_vis(p);

            for ( const auto& pt : neighs ) process(pt, vis);
        }

        return cur; 
        } 
    };

    for     ( auto i{0}; i < N; ++i ) {
        for ( auto j{0}; j < N; ++j ) {
            if ( !grid[i][j].is_newland() ) continue;
            ++cmpt;
            std::set<Pos> vis;
            cur = 0;
            if ( auto curSize{ process({i,j}, vis) }; curSize > ret.second )
                ret = { cmpt, curSize };
        }
    }

    std::cout << ret.first << ' ' << ret.second << '\n';
}