#include <bits/stdc++.h>

typedef std::string         ARROW;
typedef std::pair<int, int> POS;

int main()
{
    int h, w, turns{0};
    std::map<POS, ARROW > state{};

    std::cin >> h >> w; std::cin.ignore();

    for ( auto i = 0; i < h; ++i ) {
        std::string line;
        getline(std::cin, line);
        for ( auto j = 0; j < std::size(line); ++j )
            if( line[j] != '.' ) state[std::pair{i, j}] =  line[j];
    }

    while ( !std::empty(state) ) {
        std::map< POS, ARROW > next;
        for ( auto [pos, arrow] : state ) {
            auto x{ pos.first }, y{ pos.second };
            switch(arrow[0]) {
                case '^': x = (x - 1 + h) % h; break;
                case 'v': x = (x + 1    ) % h; break;
                case '<': y = (y - 1 + w) % w; break;
                case '>': y = (y + 1    ) % w; break;
            }
            next[{x, y}] += arrow;
        }

        for ( auto it = std::begin(next); std::end(next) != it; )
            if ( std::size(it->second) > 1 ) it = next.erase(it);
            else ++it;

        state = next;
        ++turns;
    }

    std::cout << turns << '\n';
}