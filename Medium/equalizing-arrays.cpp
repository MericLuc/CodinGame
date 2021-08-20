#include <bits/stdc++.h>

template <typename T>
using V = std::vector<T>;

int main()
{
    int                       N; std::cin >> N;
    V<int>                    a1(N), a2(N);
    V<std::list<std::pair<int, int>>> movesVec(N);


    for ( auto& elm : a1 ) std::cin >> elm;
    for ( auto& elm : a2 ) std::cin >> elm;

    int curDiff{ 0 }, totalMoves{ 0 };
    for ( auto i = 0; i < N; ++i ) {
        if ( curDiff ) {
            ++totalMoves;
            if ( curDiff > 0 ) movesVec[i    ].emplace_back(-1,  curDiff);
            else               movesVec[i - 1].emplace_back( 1, -curDiff);
        }
        curDiff += a2[i] - a1[i];
    }

    std::cout << totalMoves << "\n";

    for ( int i = 0; i < N; ++i ) {
        while ( i >= 0 && !std::empty(movesVec[i]) ) {
            auto [D, V] = movesVec[i].front();

            if (a1[i] < V) 
                break;

            a1[i    ] -= V;
            a1[i + D] += V;
            
            movesVec[i].pop_front();

            std::cout << i-- + 1 << " " << D << " " << V << "\n";
        }
    }
}