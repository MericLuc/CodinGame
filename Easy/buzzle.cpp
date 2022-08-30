#include <bits/stdc++.h>

int sum_of_digits(int n, int base = 10) {
    int ret{ 0 };

    while ( 0 != n ) { ret += n % base; n /= base; }
    return ret;
}

bool buzzle(int num, int base, const std::vector<int>& tests ) {
    for ( const auto& i : tests ) 
        if ( (0 == num % i) || (i == num % base) ) return true;
    return ( num < base ) ? false : buzzle( sum_of_digits(num, base), base, tests );
}

int main()
{
    int base, a, b;
    std::cin >> base >> a >> b; std::cin.ignore();

    std::vector<int> tests{ ++std::istream_iterator<int>(std::cin),
                              std::istream_iterator<int>() };

    for ( auto num = a; num <= b; ++num ) {
        std::cerr << "num : " << num << '\n';
        std::cout << ( buzzle(num, base, tests) ? "Buzzle" : std::to_string(num) ) << '\n';
    }
}