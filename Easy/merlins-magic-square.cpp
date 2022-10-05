#include <bits/stdc++.h>

class MSquare {
public:
    MSquare(std::istream& is) noexcept {
        std::string line;
        for ( auto i{ 0 }; i < 3; ++i ) { 
            if ( getline(is, line); std::size(line) < 5 ) continue;

            std::list<uint8_t> to_set{};
            for ( auto cmpt{ 0 }; cmpt < 3; ++cmpt ) 
                if ( '*' == line[2 * cmpt] ) to_set.emplace_back( 3 * i + cmpt + 1 );
            set_list(to_set);
        }
    }

    MSquare toggle(uint8_t cell) noexcept {
        MSquare ret{ *this };

        switch( cell ) {
            case 1: { ret.toggle_list({1, 2, 4, 5   }); } break;
            case 2: { ret.toggle_list({1, 2, 3      }); } break;
            case 3: { ret.toggle_list({2, 3, 5, 6   }); } break;
            case 4: { ret.toggle_list({1, 4, 7      }); } break;
            case 5: { ret.toggle_list({2, 4, 5, 6, 8}); } break;
            case 6: { ret.toggle_list({3, 6, 9      }); } break;
            case 7: { ret.toggle_list({4, 5, 7, 8   }); } break;
            case 8: { ret.toggle_list({7, 8, 9      }); } break;
            case 9: { ret.toggle_list({5, 6, 8, 9   }); } break;
            default:                                      break;
        }
        return ret;
    }
    MSquare toggle(const std::string& cells) noexcept {
        MSquare ret{ *this };
        for ( const auto& c : cells ) 
            if ( std::isdigit(c) )
                ret = ret.toggle(c - '0');
        return ret;
    }
    bool    solved(void) const noexcept { return 0x1EF == (_s & 0x1EF ); }

protected:
    void toggle_list(const std::list<uint8_t>& list ) noexcept {
        for ( const auto& e : list ) _s ^= 1UL << (e-1);
    }
    void set_list(const std::list<uint8_t>& list ) noexcept {
        for ( const auto& e : list ) _s |= 1UL << (e-1);
    }

protected:
    uint16_t _s{ 0 };
};

int main()
{
    int         ret            { 1 };
    std::string buttons_pressed{ };
    MSquare     game           { std::cin };
    
    getline(std::cin, buttons_pressed);
    game = game.toggle(buttons_pressed);

    for (; ret < 10; ++ret )
        if ( auto next{ game.toggle(ret) }; next.solved() ) break;
    std::cout << ret << '\n';
}



/*

// A wayyyy simpler (and more elegant) solution for Uudu

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

constexpr int END{0b111'101'111'0};

constexpr int B1{1 << 1 | 1 << 2 | 1 << 4 | 1 << 5};
constexpr int B2{1 << 1 | 1 << 2 | 1 << 3};
constexpr int B3{1 << 2 | 1 << 3 | 1 << 5 | 1 << 6};
constexpr int B4{1 << 1 | 1 << 4 | 1 << 7};
constexpr int B5{1 << 2 | 1 << 4 | 1 << 5 | 1 << 6 | 1 << 8};
constexpr int B6{1 << 3 | 1 << 6 | 1 << 9};
constexpr int B7{1 << 4 | 1 << 5 | 1 << 7 | 1 << 8};
constexpr int B8{1 << 7 | 1 << 8 | 1 << 9};
constexpr int B9{1 << 5 | 1 << 6 | 1 << 8 | 1 << 9};

// 0 based index
constexpr int moves[] = {
    B1, B2, B3, B4, B5, B6, B7, B8, B9,
};

int main() {
  int board = 0;
  for (int i = 1; i < 10; ++i) {
    string str;
    cin >> str;
    if ("*" == str) {
      board |= 1 << i;
    }
  }

  string all_buttons_pressed;
  cin >> all_buttons_pressed;
  
  for (char c : all_buttons_pressed) {
    int i = c - '1';
    board ^= moves[i];
  }

  for (int i = 0; i < 9; ++i) {
    if ((board ^ moves[i]) == END) {
        cout << i+1 << endl;
    }
  }

}

*/