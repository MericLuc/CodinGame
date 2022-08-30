#include <bits/stdc++.h>

int main()
{
    int N, K, S, i{ 0 };
    std::cin >> N >> K; std::cin.ignore();

    std::vector<int> Li{ std::istream_iterator<int>(std::cin),
                         std::istream_iterator<int>() };

    std::sort(std::begin(Li), std::end(Li));

    while ( ++i<N && K ) {
        S  = i * ( Li[i] - Li[0] );

        if ( K > S ) { Li[0]  = Li[i]; K -= S; }
        else         { Li[0] += K/i;   K  = 0; }
    }

    std::cout << ( K ? ( K % N ? 1 : 0 ) : Li[N-1] - Li[0] );
}