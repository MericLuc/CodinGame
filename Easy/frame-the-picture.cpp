#include <bits/stdc++.h>

int main() {
    std::string pattern, padding;
    std::getline(std::cin, pattern);

    auto reverse_pattern{pattern}, reverse_padding{padding};
    std::reverse( std::begin(reverse_pattern), std::end(reverse_pattern));

    int h, w, p(pattern.size());
    std::cin >> h >> w; std::cin.ignore();

    std::vector<std::string> frame(h), border;
    for ( auto& l : frame ) {
        getline(std::cin, l);
        l.resize(w, ' ');
    }

    for ( auto i = 0; i <= p; ++i ) {
        auto line       = std::string( w + 2 * ( 1 + p - i), i < p ? pattern[i] : ' ' );
        padding         = pattern.substr(0, i);
        reverse_padding = padding;
        std::reverse(std::begin(reverse_padding), std::end(reverse_padding));
        line            = padding + line + reverse_padding;
        border.insert(std::begin(border), line);

        std::cout << line << "\n";
    }

    for ( auto& l : frame )
        std::cout << pattern + " " + l + " " + reverse_pattern << "\n";

    for ( auto& l : border )
        std::cout << l << "\n";
}