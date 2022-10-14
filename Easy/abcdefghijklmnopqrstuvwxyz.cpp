#include <bits/stdc++.h>

struct Pt { int  x, y; };

struct Cell {
    Pt    _pos;
    char  _val;
    Cell* _prev{ nullptr };
    bool  _verified{ false };

    Pt operator+(const Pt& o) noexcept { return { _pos.x + o.x, _pos.y + o.y }; }
    friend std::ostream& operator<<(std::ostream& o, const Cell& c) noexcept { 
        return o << (c._verified ? c._val : '-'); }
};

class Grid {
public:
    Grid(const std::vector< std::string >& data) noexcept :
    _width { std::size(data[0]) },
    _height{ std::size(data   ) }
    {
        _grid.reserve( _width * _height );
        for ( auto i{ 0 }; i < _height; ++i )
            for ( auto j{ 0 }; j < _width; ++j )
                _grid.push_back( { {i,j}, data.at(i).at(j) } );
    }
    Cell* at(Pt p) noexcept { 
        return (p.x>=0 && p.y>=0 && p.x<_height && p.y<_width) ? &_grid[p.y + p.x*_width] : nullptr;
    }
    const std::vector<Cell>& data(void) noexcept { return _grid; }

    auto width (void) const noexcept { return _width;  }
    auto height(void) const noexcept { return _height; }
private:
    std::vector<Cell> _grid;
    const size_t      _width, _height;
};

static constexpr Pt DIRS[]{ {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

int main()
{
    std::cin.ignore(std::numeric_limits<int>::max(), '\n');
    std::vector< std::string > data{ std::istream_iterator<std::string>(std::cin), 
                                     std::istream_iterator<std::string>() };

    Grid              grid{ data };
    std::stack<Cell*> open;
    for     ( auto i{ 0 }; i < grid.height(); ++i )
        for ( auto j{ 0 }; j < grid.width() ; ++j )
            if ( 'a' == data[i][j] ) 
                open.push( grid.at({i, j}) );

    while ( !std::empty(open) ) {
        auto cur{ open.top() };
        open.pop();

        if ( 'z' == cur->_val ) {
            while ( cur ) {
                cur->_verified = true;
                cur = cur->_prev;
            } 
            continue;
        }
        std::for_each( std::cbegin(DIRS), std::cend(DIRS), [&](const auto& dir) {
            auto next{ grid.at(*cur + dir) };
            if ( nullptr != next && (next->_val == cur->_val + 1) ) {
                next->_prev = cur;
                open.push(next);
            }
        });
    }

    for     ( auto i{ 0 }; i < grid.height(); ++i ) {
        for ( auto j{ 0 }; j < grid.width() ; ++j ) {
            std::cout << (*grid.at({i,j}));
        }
        std::cout << '\n';
    }
}