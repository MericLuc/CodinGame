#include <bits/stdc++.h>

long long fib(long long num) noexcept {
    if ( 1 >= num ) return num;

    long long i{ 0 }, j{ 1 }, tmp{ 0 };
    while ( j <= num ) { tmp = i, i = j, j += tmp; }
    return i;
}

int main() {
    long long            input, cur;
    std::list<long long> zeckendorf{};

    std::cin >> input; std::cin.ignore();

    while ( 0 < input ) {
        cur = fib( input );
        zeckendorf.push_back(cur);
        input -= cur;
    }

    std::stringstream ss;
    std::string       output;
    for ( const auto& elm : zeckendorf ) { ss << elm << '+'; }
    output = ss.str();
    if ( output.ends_with('+') ) { output.pop_back(); }
    std::cout << output << std::endl;
}
