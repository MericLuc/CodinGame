#include <iostream>
#include <algorithm>

using namespace std;

typedef struct _Pt { int val, vis; } Pt;

int H, N, h;
Pt  grid[21][21];

void check(int i, int j, pair<int, int>& cur) {
    if     ( i < 0 || i > N-1 || j < 0 || j > N-1 ) { return; }
    if     ( grid[i][j].vis == 0 ) {
        grid[i][j].vis = 1;
        if ( grid[i][j].val <= H ) {
            cur.first++; 
            cur.second = min(cur.second, grid[i][j].val);
            check(i+1, j  , cur);
            check(i-1, j  , cur);
            check(i  , j+1, cur);
            check(i  , j-1, cur);
        }
    }
}

int main() {
    cin >> H >> N; cin.ignore();
    pair<int, int> res = make_pair(0, 0);
    
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N && cin >> h; j++) { grid[i][j] = { h , 0 }; }
    
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) { 
            if ( grid[i][j].val <= H && grid[i][j].vis == 0 ) {
                pair<int, int> cur = make_pair(0, H);
                check(i, j, cur);
                if      ( cur.first >  res.first ) { res = cur; }
                else if ( cur.first == res.first ) { if(cur.second < res.second) { res.second = cur.second; } }
            }
        }
    cout << res.second << endl;
}