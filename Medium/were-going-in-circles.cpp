#include <bits/stdc++.h>

#define EMPTY '.'
#define RIGHT '>'
#define LEFT  '<'
#define UP    '^'
#define DOWN  'v'

void nextPos(std::pair<int, int>& pos, const char& curDir, char& lastDir) {
    switch( curDir ) {
        case RIGHT: ++pos.second; break;
        case LEFT : --pos.second; break;
        case UP   : --pos.first ; break;
        case DOWN : ++pos.first ; break;
        case EMPTY: nextPos(pos, lastDir, lastDir); break;
    }
    if ( EMPTY != curDir ) lastDir = curDir;
}

int main()
{
    int w, h, ret{0};
    std::cin >> w >> h; std::cin.ignore();

    std::set< std::pair<int, int> > vis, curVis;
    std::vector< std::string >       grid(h);
    for ( auto& line : grid )
        std::cin >> line; std::cin.ignore();

    for     ( auto i = 0; i < h; ++i ) {
        for ( auto j = 0; j < w; ++j ) {
            std::pair<int, int> pos     = {i, j};
            const auto          initPos = pos;
            auto                lastDir = grid[i][j];

            if ( EMPTY == grid[i][j] || vis.count(pos) ) continue;
            curVis.clear();

            while ( pos.first  >= 0 && pos.first  < h && 
                    pos.second >= 0 && pos.second < w && 
                    !curVis.count(pos) ) {

                const auto& curDir = grid[pos.first][pos.second];

                if ( EMPTY != curDir ) { curVis.insert(pos); }

                nextPos(pos, curDir, lastDir);

                if ( pos == initPos ) { 
                    ++ret; 
                    vis.insert(std::begin(curVis), std::end(curVis)); 
                    break; 
                }
            }
        }
    }

    std::cout << ret << "\n";
}