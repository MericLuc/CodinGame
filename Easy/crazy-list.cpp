#include <bits/stdc++.h>

#define MOD 3
#define PRV(i,j)   ( ((i-j) % MOD + MOD) % MOD )

int main() {

    std::array<long int, MOD> in;
    long int                  idx{ 0 }, cmpt{ 0 };

    while ( std::cin >> in[idx] ) { cmpt++; idx = (idx + 1) % 3; }

    if ( 1 >= cmpt ) 
        return EXIT_FAILURE;
    
    long int ret{ in[0] }, x{ in[PRV(idx, 3)] }, y{ in[PRV(idx, 2)] }, z{ in[PRV(idx, 1)] };

    if ( y != x ) {
        long int A{ ( (z - y) / (y - x) ) }, B{ y - A * x };
        ret = z * A + B;
    } 

    std::cout << ret << std::endl;
}