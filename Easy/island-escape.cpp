#include <bits/stdc++.h>

struct Cell {
    int  val{ 0 };
    bool visited{ false };
};

struct Point {
    int x, y; 
    constexpr Point(int x_ = 0, int y_ = 0) noexcept : x{x_}, y{y_} {} 
};

Point operator+(const Point& a, const Point& b) { 
    return {a.x + b.x, a.y + b.y}; 
}

class Grid {
private:
    std::vector< std::vector<Cell> > _cells;
    const int _size;

public:
    Grid(int n) noexcept : 
        _size{ n }, _cells{ static_cast<size_t>(n), std::vector<Cell>(n) } {}

    Cell& at(const Point& p) noexcept {
        return _cells.at(p.x).at(p.y);    
    } 
    std::vector<Cell>& operator[](int i) noexcept {
        return _cells[i];
    }

    auto begin() noexcept { return _cells.begin(); }
    auto end() noexcept { return _cells.end(); }  
};

int main() {
    constexpr Point dirs[]{ {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

    int n;
    std::cin >> n; std::cin.ignore();

    Grid grid{n};
    for ( auto& raw : grid )
        for ( auto& cell : raw )
            std::cin >> cell.val; std::cin.ignore();

    Point             curPos { n/2, n/2 };
    Cell*             curCell{ nullptr  };
    std::deque<Point> stack;
    stack.push_back(curPos);

    while (!stack.empty()) {
        curPos  = stack.front();
        stack.pop_front();

        curCell = &grid.at(curPos);
        curCell->visited = true;

        if ( 0 == curCell->val )
            break;

        for ( const auto& dir : dirs ) {
            Point nxtPos{ curPos + dir };
            if ( nxtPos.x < 0 || nxtPos.x >= n || 
                 nxtPos.y < 0 || nxtPos.y >= n ) continue;
            
            Cell* nxtCell{ &grid.at(nxtPos) };
            if ( nxtCell->visited || (1 < abs(curCell->val - nxtCell->val)) ) continue;
            
            stack.push_back(nxtPos);
        }
    }

    std::cout << (( 0 == curCell->val ) ? "yes" : "no" ) << std::endl;
}