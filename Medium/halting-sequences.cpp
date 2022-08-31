#include <bits/stdc++.h>

struct T : std::pair<int, int> { };
std::istream& operator>>(std::istream& is, T& in) { return is >> in.first >> in.second; }

int main()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::vector<std::pair<int, int> > test{ std::istream_iterator<T>(std::cin),
                                            std::istream_iterator<T>() };
    
    for ( const auto& [a, b]: test ) {
        int tmp{ (a + b)/std::__gcd(a, b) };
        std::cout << ( (0 == (tmp & (tmp - 1))) ? "halts" : "loops" ) << '\n';
    }
}