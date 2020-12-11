#include <bits/stdc++.h>
using namespace std;

int main() {
    string row;
    double res{0};
    int    W, H; cin >> W >> H; cin.ignore();

    for (int i = 0; i < H && getline(cin, row); i++)
        for ( auto&& c : row )
            if ( c != '.' ) { res += ( c == 'X' ) ? 1 : 0.5; }
    res /= W*H;
    cout << ( (res > 0.8)?"Rectangle":((res > 0.6 )?"Ellipse":"Triangle") ) << endl;
}