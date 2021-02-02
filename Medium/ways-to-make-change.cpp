#include <bits/stdc++.h>

int waysToChange(int N, std::vector<int> V ) {
    std::vector<int> ways(N+1, 0);
    ways[0] = 1;

    for    ( auto& it : V )
        for  ( int i = 1; i <= N; i++ )
            if ( it <= i ) { ways[i] += ways[i-it]; }

  return ways[N];
}

int main() {
    int N; std::cin >> N;

    std::istream_iterator<int> it(std::cin), eos;
    std::vector<int>           v (++it, eos);

    std::cout << waysToChange(N, v) << std::endl;
}