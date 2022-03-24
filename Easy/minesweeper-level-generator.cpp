#include <bits/stdc++.h>

class Board {
  public:
    Board(const std::vector<int>& i) :
        _w(i[0]), _h(i[1]), _n(i[2]), _rng(i[5]), _grid(_h, std::string(_w, '.')) {
        int mines{ 0 }, x, y, xi(i[3]), yi(i[4]);
        do {
            x = _rng.nxt() % _w, y = _rng.nxt() % _h;
            if ( '#' !=  _grid[y][x] &&
                    (abs(y - yi) > 1 || abs(x - xi) > 1) ) ++mines,  _grid[y][x] = '#';
        } while ( mines < _n );

        for     ( int i = 0; i < _h; ++i )
            for ( int j = 0; j < _w; ++j )
                if ( '.' == _grid[i][j] ) _grid[i][j] = _compute_neighbours(i, j);

    }
    friend std::ostream& operator<<(std::ostream& o, const Board& b) {
        for ( const auto& line : b._grid ) o << line << '\n';
        return o;
    }
  private:
    class PRNG {
      public:
        PRNG(int seed): _val{static_cast<uint32_t>(seed)} {}
        uint32_t cur(void) const { return _val; }
        uint32_t nxt(void) { _val = ( 214013 * _val + 2531011 ) / 65536; return _val; }
      private:
        uint32_t _val;
    };

    char _compute_neighbours(int x, int y) {
        int ret{ 0 };
        for     ( int i = std::max(0, x - 1); i <= std::min(x + 1, _h - 1); ++i )
            for ( int j = std::max(0, y - 1); j <= std::min(y + 1, _w - 1); ++j )
                if ( '#' == _grid[i][j] ) ++ret;
        return 0 == ret ? '.' : ret + '0';
    }

  private:
    int   _w, _h;                   /*< Dimensions of the board        */
    int   _n;                       /*< Number of mines                */
    PRNG _rng;                      /*< Pseudo random number generator */
    std::vector<std::string> _grid; /*< Generated grid */
};

int main() {
    std::vector<int> in{std::istream_iterator<int>(std::cin),
                        std::istream_iterator<int>() };
    if ( 6 != std::size(in) ) return EXIT_FAILURE;

    std::cout << Board(in);
}