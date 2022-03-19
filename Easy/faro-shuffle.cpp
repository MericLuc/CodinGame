#include <bits/stdc++.h>

int main() {
    int         N, half;
    std::cin >> N; std::cin.ignore();

    std::vector<std::string> dck(std::istream_iterator<std::string> {std::cin},
                                 std::istream_iterator<std::string> {});

    half = std::ceil(std::size(dck) / 2.);

    while ( N-- ) {
        auto lhs = std::vector<std::string>(std::begin(dck), std::begin(dck) + half);
        auto rhs = std::vector<std::string>(std::begin(dck) + half, std::end(dck)  );

        auto lit{ std::begin(lhs) }, rit{ std::begin(rhs) };
        for ( auto i = 0; i < std::size(dck); ++i )
            dck[i] = ( 0 == i % 2 ) ? *lit++ : *rit++;
    }

    std::stringstream ss;
    for ( const auto& l : dck ) ss << l << " ";
    auto ret = ss.str();
    ret.pop_back();
    std::cout << ret;
}