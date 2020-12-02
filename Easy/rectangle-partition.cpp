#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std;

main()
{
    int w, h, x_mes, y_mes, res(0), tmp;
    cin >> w >> h >> x_mes >> y_mes; cin.ignore();
    set<int>       l_x = { 0, w }, l_y = { 0, h };
    map<int, int > map_x, map_y;
    
    map_x[w] = 1; map_y[h] = 1;
    for (int i = 0; i < x_mes && cin >> tmp; i++) { 
        for ( auto& it : l_x ) { map_x[abs(it - tmp)] ++; }
        l_x.insert(tmp); cin.ignore(); 
    }
    for (int i = 0; i < y_mes && cin >> tmp; i++) {  
        for ( auto& it : l_y ) { map_y[abs(it - tmp)] ++; }
        l_y.insert(tmp); cin.ignore(); 
    }
    
    for ( auto &it : map_x )
        if ( map_y.find(it.first) != map_y.end() ) { res += it.second * map_y[it.first]; }
    cout << res << endl;
}