#include <bits/stdc++.h>

template <typename T>
using V = std::vector<T>;

int sumDigits(int n) noexcept {
    int res{ 0 };
    while( n > 0 ) { res += n % 10; n /= 10; }   
    return res;
}

int main()
{
    int r, c, t;
    std::cin >> r >> c >> t; std::cin.ignore();

    V< V<int> > mem{ static_cast<size_t>(r), V<int>(c, 0) };
    for     ( auto i{ 0 }; i < r; ++i )
        for ( auto j{ 0 }; j < c; ++j )
            mem[i][j] = sumDigits(i) + sumDigits(j);
    
    std::function<int(int, int)> doTheJob{ [&](int row, int col){
        if ( row >= r || col >= c || mem[row][col] > t )
            return 0;

        mem[row][col] = t + 1;
        
        return doTheJob(row, col + 1) + doTheJob(row + 1, col) + 1;
    } };

    std::cout << doTheJob(0, 0) << '\n';
}