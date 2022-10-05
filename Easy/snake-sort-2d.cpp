#include <bits/stdc++.h>

typedef std::istream IS;
typedef std::ostream OS;

struct Apple {
    friend IS& operator>>(IS& is,       Apple& in ) { return is >> in._name >> in._row >> in._col; }
    friend OS& operator<<(OS& os, const Apple& out) { return os << out._name; }

    std::string _name;
    int         _row, _col;
};

int main()
{
    int                                N;
    Apple                              cur_apple;
    std::map<int, std::vector<Apple> > apples;

    std::cin >> N;
    for ( auto i{0}; i < N; ++i ) {
        std::cin >> cur_apple;
        apples[cur_apple._row].push_back(cur_apple);
    }

    auto right{ true };
    std::stringstream ss;
    for ( auto& [row, apple_row] : apples ) {
        std::sort(std::begin(apple_row), 
                  std::end  (apple_row), 
                  [&right](const auto& a, const auto& b){
                    return right ? a._col < b._col : b._col < a._col; 
                  });
        right = !right; 
        for ( const auto& apple : apple_row )
            ss << apple << ',';
    }
    auto ret{ ss.str() };
    if ( !std::empty(ret) ) ret.pop_back();
    std::cout << ret;
}