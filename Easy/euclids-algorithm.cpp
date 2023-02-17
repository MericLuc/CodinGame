#include <bits/stdc++.h>

int gcd_steps(int a, 
              int b) noexcept {
    if ( 0 == b )
        return a;
    int aa{ a / b }, bb{ a % b };
    std::cout << a << '=' << b << '*' << aa << '+' << bb << '\n';
    return gcd_steps(b, bb);
}

int main()
{
    int a, b;
    std::cin >> a >> b;

    auto gcd{ gcd_steps(a,b) };
    std::cout << "GCD(" << a << ',' << b << ")=" << gcd << '\n';
}