#include <bits/stdc++.h>

struct CoinEntry { int val, nb; };

int main()
{
    int goal, nbTypes;
    std::cin >> goal >> nbTypes; std::cin.ignore();

    std::vector<CoinEntry> vData(nbTypes);
    for ( int i{ 0 }; i < nbTypes; ++i ) std::cin >> vData[i].nb;
    for ( int i{ 0 }; i < nbTypes; ++i ) std::cin >> vData[i].val;

    std::sort( std::begin(vData), 
               std::end(vData), 
               [](const auto& a, const auto& b){return a.val < b.val; });

    int idx{ -1 }, ret{ 0 };
    while ( goal > 0 && ++idx < nbTypes ) {
        auto& cEntry{ vData[idx] };
        goal -= cEntry.nb * cEntry.val;
        ret  += ( 0 >= goal ) ? cEntry.nb - abs(goal) / cEntry.val : cEntry.nb;
    }

    std::cout << ((goal > 0) ? -1 : ret) << std::endl;
}