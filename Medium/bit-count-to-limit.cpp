#include <iostream>

int main()
{
    uint32_t n, rL{0}, rP{0}, ret{0};
    std::cin >> n;

    while ( n ) {
        if ( n & 1 ) {
            ret += rL << (rL -1);
            ret += rP + 1;
            rP  |= 1 << rL;
        }
        n >>= 1;
        ++rL;
    }

    std::cout << ret << std::endl;
}