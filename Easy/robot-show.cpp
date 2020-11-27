#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int    L, N, l_cur;
    cin >> L >> N; cin.ignore();
    vector<int> v(N);

    for ( int i = 0; i < N; i++ ) { cin >> v[i]; }

    const auto [ l_min, l_max ] = minmax_element( v.begin(), v.end() );
    cout << std::max(L - *l_min, *l_max) << endl;
}