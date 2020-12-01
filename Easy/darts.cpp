#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

typedef struct score {
    string name;
    int    sc;
    int    pos;
    
    score(const string& p_name = "", const int p_sc = 0, const int p = 0): name(p_name), sc(p_sc), pos(p) {};
} score;

bool sortbyPlayers( const score& a, const score& b ) { 
    if ( a.sc == b.sc ) return (a.pos < b.pos);
    else                return (a.sc  > b.sc ); 
} 

main() {
    int w, N, T, x, y;
    vector< score > v;
    cin >> w >> N; cin.ignore();
     
    for (int i = 0; i < N; i++) { string name; getline(cin, name); v.push_back(score(name,0,i)); }
   
    cin >> T; cin.ignore();
    for (int i = 0; i < T; i++) {
        string throwName; cin >> throwName >> x >> y; cin.ignore();
        auto it = find_if(v.begin(), v.end(), [&throwName](const score& obj) {return obj.name == throwName;} );
        if ( (abs(x) <= w/2) && (abs(y) <= w/2) )
            if      ( abs(x)+abs(y)     <= w/2  ) { it->sc += 15; }
            else if ( sqrt( x*x + y*y ) <= w/2  ) { it->sc += 10; }
            else                                  { it->sc += 5;  }
    }
    sort(v.begin(), v.end(), sortbyPlayers);
    for (auto const& i : v ) cout << i.name << " " << i.sc << endl;
}