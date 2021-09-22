#include <bits/stdc++.h>

int main() {
    long long N;
    std::cin >> N;
    std::cout << (8*N*N*N - 3*N*N + 4*N - (6*N*N-3) * (N%2))/6;
}