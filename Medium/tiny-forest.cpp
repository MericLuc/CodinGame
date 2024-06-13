#include <bits/stdc++.h>

struct Pos {
    int        x, y;
    static int w, h;
    bool operator<(const Pos& o) const noexcept { return o.y != y ? y < o.y : x < o.x; }
    operator bool() const noexcept { return (0 <= x) && (w > x) && (0 <= y) && (h > y); }
};

int           Pos::w{ 0 }, Pos::h{ 0 }, res{ 0 };
std::set<Pos> trees;
enum ACTION{ COUNT = 2, INSERT};

int perform( const Pos& p, ACTION act ) {
    int res{ 0 }, val{ static_cast<int>(act) };
    for     ( int i{ -val }; i <= val; ++i ) 
        for ( int j{ -val + abs(i) }; j <= val - abs(i); ++j ) 
            if(  Pos nxt{ p.x + j, p.y + i}; nxt ) 
                if      (INSERT == act          ) { trees.insert(nxt); }
                else if ( 0 == trees.count(nxt) ) { res++;             }
    return res;
}

int main() {
    std::string   input;
    std::cin >> Pos::w >> Pos::h; 
    std::cin.ignore();

    for    ( int y{ 0 }; y < Pos::h && getline(std::cin, input); ++y ) 
        for( int x{ 0 }; x < Pos::w; ++x )
            if ( 'Y' == input[x] ) perform( {x, y}, INSERT );

    for     ( int y{ 0 }; y < Pos::h; ++y )
        for ( int x{ 0 }; x < Pos::w; ++x )
            res = std::max(res, perform( {x, y}, COUNT ));

    std::cout << std::size(trees) + res;
}