#include <bits/stdc++.h>

int main() {
    int                sz, oddQuad, oddValue, standardValue, qRow, qCol;
    std::map<int, int> sums, cmpts;

    std::cin >> sz; std::cin.ignore();

    for (int i{ 0 }; i < sz; i++) {
        std::string row;
        getline(std::cin, row);
        qRow = (i < sz / 2 ) ? 0 : 1;
        for ( int j{ 0 }; j < std::size(row); ++j ) {
            qCol = (j < sz / 2 ) ? 0 : 1;
            if ( '.' != row[j] ) { sums[qRow * 2 + qCol + 1] += row[j] - '0'; }
        }
    }

    for (const auto& [k,v] : sums) { cmpts[v]++; }
    for (const auto& [k,v] : sums) { 
        if ( 1 == cmpts[v] ) { oddValue = v, oddQuad  = k; }
        else                 { standardValue = v;          }
    }

    std::cout << "Quad-" << oddQuad << " is Odd-Quad-Out" << std::endl;
    std::cout << "It has value of " << oddValue           << std::endl;
    std::cout << "Others have value of " << standardValue << std::endl;
}