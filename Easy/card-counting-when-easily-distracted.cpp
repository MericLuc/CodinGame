#include <bits/stdc++.h>

int doTheJob(const std::string& s, int threshold) noexcept {

    static const std::map<char, int> values{ 
        { 'K', 10 }, { 'Q', 10 }, { 'J', 10 }, { 'T', 10 },
        { '9',  9 }, { '8',  8 }, { '7',  7 }, { '6',  6 },
        { '5',  5 }, { '4',  4 }, { '3',  3 }, { '2',  2 }, { 'A', 1 }
    };

    static const std::regex rgx("^([2-9]|K|Q|J|T|A)+$",
                                std::regex_constants::ECMAScript);

    int                cardsLeft{ 52 };
    std::map<int, int> deck{ {10, 16} };
    for ( auto i{1}; i < 10; ++i ) deck[i] = 4;

    std::string              tkn;
    std::istringstream       iss{ s };
    while ( std::getline(iss, tkn, '.') ) {
        if ( !std::regex_search(tkn, rgx) ) continue;

        for ( const auto& c : tkn ) { --deck[ values.at(c) ];  }
        cardsLeft -= std::size(tkn);
    }

    int    cnt{ 0 };
    for ( const auto& [val, nb]: deck )
        if ( val < threshold ) { cnt += nb; }

    return std::round(cnt * 100.0 / cardsLeft);
}

int main()
{
    std::string SoC;
    int         thsh;

    getline(std::cin, SoC);
    std::cin >> thsh;

    std::cout << doTheJob(SoC, thsh) << "%\n";
}