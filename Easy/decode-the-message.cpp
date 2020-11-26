#include <bits/stdc++.h>

int main() {
    long long    P; std::cin >> P; std::cin.ignore();
    std::string C, res; std::getline(std::cin, C);

    while ( P >= 0 ) { res += C[ P % C.size() ]; P = P / C.size() - 1; } 

    std::cout << res << std::endl;
}