#include <bits/stdc++.h>

template < size_t Sz, typename=std::enable_if_t< (Sz>0) > >
class SC {
public:
static const size_t ROWS{ 7 };

SC(std::istream& is = std::cin) {
    std::string buf;
    for ( auto row{ 0 }; row < ROWS; ++row ) {
        std::getline(std::cin, buf);

        if ( 8 * Sz + 1 > std::size(buf) )
            throw std::runtime_error("Invalid input size");

        _parseRow(row, buf);
    }
}

SC& operator+=(const SC& o) noexcept {
    assert(size() == o.size());

    for ( auto i{ 0 }; i < size(); ++i ) {
        _segs[i] += o._segs[i];
    }
    return *this;
}
SC& operator-=(const SC& o) noexcept {
    assert(size() == o.size());

    for ( auto i{ 0 }; i < size(); ++i ) {
        _segs[i] -= o._segs[i];
    }

    return *this;
}

int score(void) const noexcept { 
    auto ret{ 0 };

    for ( const auto& seg : _segs) {
        ret *= 10;
        ret += seg.value();
    }
    
    return ret;
}
auto size(void) const noexcept { return std::size(_segs); }

private:
    class SevenSegment {
        public:
            SevenSegment(uint8_t val = 0) noexcept : _val{ val } {}
            void    set(uint8_t idx, bool val) noexcept {
                _val ^= (-val ^ _val) & (1U << idx);
            }
            uint8_t get(uint8_t idx) noexcept { return (_val >> idx) & 1U; }
            void    clear(uint8_t idx) noexcept { _val &= -( 1U << idx); }
            
            int value(void) const { 
                static const std::map<uint8_t, uint8_t> _convs {
                    { 0b00111111, 0}, { 0b00000110, 1}, { 0b01011011, 2},
                    { 0b01001111, 3}, { 0b01100110, 4}, { 0b01101101, 5},
                    { 0b01111101, 6}, { 0b00000111, 7}, { 0b01111111, 8}, { 0b01101111, 9}
                };
                
                if ( std::end(_convs) == _convs.find(_val) )
                    throw std::runtime_error("unknown segment value");
                return _convs.at(_val);
            }

            SevenSegment& operator+=(const SevenSegment& o) noexcept {
                _val |= o._val;
                return *this;
            }
            SevenSegment& operator-=(const SevenSegment& o) noexcept {
                _val = (_val | o._val) ^ o._val;
                return *this;
            }

        private:
            uint8_t _val;
    };

    void _parseRow(int row, const std::string& buf) noexcept {
        static const std::map<int, std::list<std::pair<int, int>> > _stPos{ 
            { 0 , {} },
            { 1 , { {0, 3} }},
            { 2 , { {1, 6}, {5, 2} }},
            { 3 , { {6, 3} }},
            { 4 , { {2, 6}, {4, 2} }},
            { 5 , { {3, 3} }},
            { 6 , {} }
        };

        for ( const auto& [idx, pos] : _stPos.at(row) ) {
            auto offset{ 0 };
            for ( auto i{ 0 }; i < Sz; ++i ) {
                _segs[i].set(idx, !std::isspace(buf[offset + pos]) );
                offset += 8;
            }
        }
    }

private:
    std::array<SevenSegment, Sz> _segs;
};

int main() {
    SC<2> scoreBoard;
    std::cin.ignore(std::numeric_limits<int>::max(), '\n');
    scoreBoard -= SC<2>();
    std::cin.ignore(std::numeric_limits<int>::max(), '\n');
    scoreBoard += SC<2>();

    std::cout << std::setw(2) << std::setfill('0') << scoreBoard.score() << '\n';
    return EXIT_SUCCESS;
}