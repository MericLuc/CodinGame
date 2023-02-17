#include <bits/stdc++.h>

struct Aircraft {
    int _row{ 0 }, _col{ 0 };
    constexpr int operator-(const Aircraft& rhs) noexcept {
        return abs(_col - rhs._col) - abs(_row - rhs._row);
    }
};

int main() 
{
    int n;
    std::cin >> n; std::cin.ignore();

    std::vector< Aircraft > aircrafts;
    Aircraft                launcher;
    std::set< int >         fireTurns;
    std::string             curLine;
    for ( auto row{ 0 }; row < n; ++row ) {
        getline(std::cin, curLine);
        for ( auto col{ 0 }; col < std::size(curLine); ++col ) {
            switch( curLine[col] ) {
                case '>' : 
                case '<' : aircrafts.push_back({row, col}); break;
                case '^' : launcher = {row, col}; break;
                default  : break;
            }
        }
    }

    for ( const auto& aircraft : aircrafts ) 
        fireTurns.insert( launcher - aircraft );
    
    for     ( auto curTurn{ 0 }; const auto& nxtFire : fireTurns ) {
        for ( auto i{ 0 }; i < (nxtFire - curTurn - 1); ++i )
            std::cout << "WAIT\n";
        std::cout << "SHOOT\n";
        curTurn = nxtFire;
    }
}