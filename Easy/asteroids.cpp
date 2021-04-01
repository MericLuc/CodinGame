#include <bits/stdc++.h>

template <typename T,typename U>                                                   
std::pair<T,U> operator-(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first-r.first,l.second-r.second};                                    
} 

int main()
{
    int W, H, T1, T2, T3;
    double dT1, dT2;
    std::string s1, s2;
    std::map< char, std::pair<int, int> > d1, d2;

    // Parse input into dictionaries
    std::cin >> W >> H >> T1 >> T2 >> T3; std::cin.ignore();
    for ( int i = 0; i < H; ++i ) {
        std::cin >> s1 >> s2; std::cin.ignore();
        for ( int j = 0; j < W; ++j ) {
            if ( s1.at(j) != '.' ) { d1[s1.at(j)] = {i, j}; }
            if ( s2.at(j) != '.' ) { d2[s2.at(j)] = {i, j}; }
        }
    }

    // Extrapolate
    std::vector<std::string> out(H, std::string(W, '.') );
    dT1 = T2 - T1, dT2 = T3 - T2;
    for ( auto [alt, P1] : d1 ) {
        std::pair<int, int> P2, Pend{0,0}, dPos;
        P2 = d2[alt];
        dPos = (P2 - P1);
        Pend.first  = P2.first  + std::floor(dPos.first  * (dT2/dT1));
        Pend.second = P2.second + std::floor(dPos.second * (dT2/dT1));

        if ( Pend.first < 0 || Pend.first >= H || Pend.second < 0 || Pend.second >= W )
            continue;

        if ( out[Pend.first][Pend.second] == '.' || out[Pend.first][Pend.second] > alt)
            out[Pend.first][Pend.second] = alt;
    }

    // Ouput
    for ( const auto& line : out )
        std::cout << line << "\n";
}
