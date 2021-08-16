#include <bits/stdc++.h>

const auto print = [](auto&& toPrint){
    std::for_each( std::begin(toPrint), std::end(toPrint), [](const auto& line) {
        std::cout << line << "\n";
    });
};

int main()
{
    int h, w, n;
    std::cin >> h >> w >> n; std::cin.ignore();

    std::map<char, std::string> states;
    getline(std::cin, states['O']);
    getline(std::cin, states['.']);

    std::istream_iterator<std::string> it(std::cin), eos;
    std::vector<std::string>           v (it, eos);

    while(n--) {
        auto tmp { v };
        auto curH{ 0 };
        std::for_each(std::begin(v), std::end(v), [&](auto&& line) {
            auto curW{ 0 };
            std::for_each( std::begin(line), std::end(line), [&](auto&& cell) {
                auto neighbours = std::invoke([&]() {
                    auto res{ 0 };
                    for(auto i = -1; i <= 1; ++i)
                        for(auto j = -1; j <= 1; ++j) {
                            auto tmpH{ curH + i }, tmpW{ curW + j };
                            if( (i || j) && (tmpH >= 0) && (tmpH < h) && (tmpW >= 0) && (tmpW < w) )
                                res += v[tmpH][tmpW] == 'O';
                        }
                    return res;
                });

                tmp[curH][curW] = ( states[cell][neighbours] == '1' ) ? 'O' : '.';
                ++curW;
            });
            ++curH;
        });
        v = std::move(tmp);
    }

    print(v);
}
