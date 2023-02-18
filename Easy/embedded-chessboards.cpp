#include <bits/stdc++.h>

struct Painting {
    int row, col, isWhite; 
    friend std::istream& operator>>(std::istream& is, Painting& p) noexcept {
        return is >> p.row >> p.col >> p.isWhite;
    }
};

int main()
{
    std::cin.ignore(std::numeric_limits<int>::max(), '\n');
    Painting P;
    for(; std::cin >> P;)
        std::cout << (P.row < 8 || P.col < 8 ? 0 :
                     ((P.row - 7) * (P.col - 7) + P.isWhite)/2) << '\n';
}