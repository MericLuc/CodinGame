#include <bits/stdc++.h>

int main()
{
    size_t res{ 0 };
    std::cin.ignore(std::numeric_limits<int32_t>::max(), '\n');
    std::vector< int32_t > bucket{ std::istream_iterator<int32_t>(std::cin),
                                   std::istream_iterator<int32_t>() };
    
    for     ( auto i{ 0 }; i < std::size(bucket);     ++i )
        for ( auto j{ std::size(bucket) - 1 }; j > i; --j )
            res = std::max(res, std::min(bucket[i], bucket[j]) * (j - i));

    std::cout << res << '\n';
}