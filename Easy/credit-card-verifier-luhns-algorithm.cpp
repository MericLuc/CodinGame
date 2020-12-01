#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

main() {
    int n; cin >> n; cin.ignore();
    for (int i = 0; i < n; i++) {
        string card; getline(cin, card);
        int res(0); 
        card.erase(remove(card.begin(), card.end(), ' '), card.end());
        for ( int j = 0; j <= 15; j++ ) {
            int tmp =  2 * ( card[j] - '0' );
            if (j%2==0) { res += ( tmp > 9 ) ? tmp - 9 : tmp;  }
            else        { res += card[j] - '0';                }
        }
        cout << ( (res % 10 == 0) ? "YES" : "NO" ) << endl;
    }
}