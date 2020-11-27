#include <iostream>
#include <string>

using namespace std;
#define loop2(i,j,h,w) for(int i=0; i<h; ++i)for(int j=0 ; j<w; ++j)

main() {
    int     h, w, sign(0);
    string  inStr;
    cin >> h >> w; cin.ignore();

    int grid_nb[h][w];
    loop2(i,j,h,w) { cin >> grid_nb[i][j]; }

    char grid_str[h][w];
    loop2(i,j,h,w) { cin >> grid_str[i][j]; }

    loop2(i,j,h,w) {
        if ( grid_str[i][j] == 'X' )
        {
            if ( sign == 0 || sign * grid_nb[i][j] < 0 ) { sign = grid_nb[i][j]; }
            else { cout << "false"; return 0; }
        }
    }
    cout << "true" << endl;
}