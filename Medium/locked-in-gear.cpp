#include <bits/stdc++.h>

struct Gear {
    int x, y, r, dir{0};
    friend std::istream& operator>>(std::istream& o, Gear& g) { return o >> g.x >> g.y >> g.r; }
    friend std::ostream& operator<<(std::ostream& o, Gear& g) { 
        static const std::map<int, std::string> outputs { {-1,"CCW"}, {0,"NOT MOVING"}, {1,"CW"} };
        return o << outputs.at(g.dir) << "\n";
    }

    bool contact(const Gear& g) const {
        return (pow(r + g.r, 2) == pow(x-g.x, 2) + pow(y-g.y, 2)) && ( x != g.x || y != g.y );
    }
};

int main()
{
    int N; 
    std::cin >> N;
    std::vector<Gear> gears(N);
    for ( auto& gear : gears ) std::cin >> gear;

    std::queue<Gear> q;
    gears.front().dir = 1;
    q.push(gears.front());

    while ( !std::empty(q) ) {
        auto cur = q.front();
        q.pop();

        std::for_each( std::begin(gears), std::end(gears), [&cur, &q](auto& g2){
            if ( cur.contact(g2) ) { 
                if ( g2.dir == cur.dir ) { std::cout << "NOT MOVING\n"; exit(0); }
                else if ( !g2.dir ) {
                    g2.dir = -cur.dir; 
                    q.push(g2); 
                }
            }
        });
    }

    std::cout << gears.back();
}