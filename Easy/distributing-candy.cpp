#include <bits/stdc++.h>

int main()
{
    int n, m, ret{ std::numeric_limits<int>::max() };
    std::cin >> n >> m; std::cin.ignore();

    std::vector<int> bags{ std::istream_iterator<int>(std::cin),
                           std::istream_iterator<int>() };
    std::sort( std::begin(bags), std::end(bags) );

    for ( int i  = 0; i <= n - m; ++i )
        ret = std::min( ret, bags[i + m - 1] - bags[i] );

    std::cout << ret << '\n';
}