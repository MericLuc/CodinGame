#include <bits/stdc++.h>

int main()
{
    std::cin.ignore(std::numeric_limits<int32_t>::max(), '\n');
    std::vector<std::string> lines{ std::istream_iterator<std::string>(std::cin),
                                    std::istream_iterator<std::string>() };

    auto sz{ std::size(lines.at(0)) };
    for ( auto i{ 0 }; i < std::size(lines); ++i ) {

        auto offset{ lines.at(i).find(lines.at(0)) };

        for ( auto j{ 0 }; j < std::size(lines.at(i)); ++j ) {
            if ( lines.at(i).at(j) != lines.at(0).at((j + sz - offset) % sz) ) {
                std::cout << "(" << j << "," << (i - 1) << ")\n";
                return EXIT_SUCCESS;
            }
        }
    }
    return EXIT_FAILURE;
}