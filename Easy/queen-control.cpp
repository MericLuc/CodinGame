#include <bits/stdc++.h>

#define QUEEN 'Q'
#define WHITE 'w'
#define BLACK 'b'
#define EMPTY '.'

struct Cell { 
    int x, y; 
    Cell(int x = 0, int y = 0) noexcept : x{x}, y{y} {} 
    operator bool() noexcept { return (0 <= x) && (8 > x) && (0 <= y) && (8 > y); }
    friend Cell operator+(const Cell& lhs, const Cell& rhs) noexcept { 
        return { lhs.x + rhs.x, lhs.y + rhs.y }; 
    }
}; 
using  Grid = std::array<std::string, 8>;
using  Move = Cell;

int main() {
    std::deque<Move> moves{ {-1, -1}, {1, 1}, {-1,  1}, {1, -1}, 
                            {-1,  0}, {1, 0}, { 0, -1}, {0,  1} };
    int              res{ 0 };
    Grid             grid;
    std::string      c;
    Cell             queen;

    getline(std::cin, c);

    for ( int i{ 0 }; i < 8; ++i ) {
        getline(std::cin, grid[i]);
        if ( auto col{ grid[i].find_first_of(QUEEN) }; std::string::npos != col )
            queen = { i, static_cast<int>(col) };
    }

    while ( !std::empty(moves) ) {
        Move curMove{ moves.front() };
        Cell curCell{ queen + curMove };
        moves.pop_front();

        while ( curCell ) {
            char& v{ grid[curCell.x][curCell.y] };

            if (!(((c[0] == WHITE) && (WHITE == v)) || ((c[0] == BLACK) && (BLACK == v)))) ++res;
            if ( EMPTY != v ) break;
            curCell = curCell + curMove;
        }
    }

    std::cout << res << std::endl;
}