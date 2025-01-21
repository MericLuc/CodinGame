#include <bits/stdc++.h>

int main() {
    int   n{ 0 };
    float t{ 0 }, r{ 0 };
    
    std::cin >> n; std::cin.ignore();
    do {
        std::cin >> r; std::cin.ignore();
        t = (t + r - 2 * t * r) / (1 - t * r);
    } while ( --n && (1 != t));

    std::cout << std::fixed << std::setprecision(4) << t << std::endl;
}
