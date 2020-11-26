#include <iostream>
#include <vector>

int main() {
    int    A1,   N;
    std::cin >> A1 >> N; std::cin.ignore();
 
    std::vector<int> dt (N,-1), sq (N, 0);

    sq[0] = A1;
    for (int i = 0; i < N ; i++ )
    {
        if ( dt[sq[i]] >= 0 ) { sq[i+1] = i - dt[sq[i]]; }
        dt[sq[i]] = i;
    }

    std::cout << sq[N-1] << std::endl;
}