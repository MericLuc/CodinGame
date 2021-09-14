#include <bits/stdc++.h>

int main() {
    int N; std::cin >> N;
    std::cout << std::fixed << std::setprecision(0) << (2 * N - pow(2,ceil(log(N)/log(2)))) << "\n";
}