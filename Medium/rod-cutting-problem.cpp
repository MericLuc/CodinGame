#include <iostream>
#include <vector>
#include <map>

int getMaxValue(int p_length, const std::map<int, int>& p_vals ) {
    std::vector<int> sums(p_length+1, 0);

    for    ( const auto& [cutL, cutV] : p_vals )
        for  ( int curL = 1; curL <= p_length; curL++ )
            if ( int resL{curL - cutL}; resL >= 0 )
                sums[curL] = std::max( sums[curL], sums[resL] + cutV);
  return sums[p_length];
}

int main() {
    int L, N, curL;
    std::map<int, int> vals;
    std::cin >> L >> N;

    for ( int i = 0; i < N; ++i )
        std::cin >> curL >> vals[curL];

    std::cout << getMaxValue(L, vals) << std::endl;
}