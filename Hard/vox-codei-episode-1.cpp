#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>
#include <map>

using namespace std;

typedef struct _Pos { int x, y; } Pos;

int dmgCalc   (vector<vector<char>>& grid, int x, int y) {
    int damage = 0;
    for (int i = x-1; i >= max(0, x-3); --i) {
        if      (grid[y][i] == '#') break;
        else if (grid[y][i] == '@') damage++;
    }
    for (int i = x+1; i <= min<int>(grid[0].size()-1, x+3); ++i) {
        if      (grid[y][i] == '#') break;
        else if (grid[y][i] == '@') damage++;
    }
    for (int i = y-1; i >= max(0, y-3); --i) {
        if      (grid[i][x] == '#') break;
        else if (grid[i][x] == '@') damage++;
    }
    for (int i = y+1; i <= min<int>(grid.size()-1, y+3); ++i) {
        if      (grid[i][x] == '#') break;
        else if (grid[i][x] == '@') damage++;
    }
    return damage;
}

void dstroy   (vector<vector<char>>& grid, int x, int y) {
    for (int i = x-1; i >= max(0, x-3); --i) {
        if      (grid[y][i] == '#') break;
        else if (grid[y][i] == '@') grid[y][i] = '.';
    }
    for (int i = x+1; i <= min<int>(grid[0].size()-1, x+3); ++i) {
        if      (grid[y][i] == '#') break;
        else if (grid[y][i] == '@') grid[y][i] = '.';
    }
    for (int i = y-1; i >= max(0, y-3); --i) {
        if      (grid[i][x] == '#') break;
        else if (grid[i][x] == '@') grid[i][x] = '.';
    }
    for (int i = y+1; i <= min<int>(grid.size()-1, y+3); ++i) {
        if      (grid[i][x] == '#') break;
        else if (grid[i][x] == '@') grid[i][x] = '.';
    }
}

int getTargets(vector<vector<char>>& grid) {
    int remainingTargets = 0;
    for (int y = 0; y < grid.size(); ++y)
        for (int x = 0; x < grid[y].size(); ++x)
            if (grid[y][x] == '@') remainingTargets++;
    return remainingTargets;
}

bool winnable (vector<vector<char>> grid, int x, int y, int bombs) {
    dstroy(grid, x, y);
    int maxDamage = 0;
    for (int y = 0; y < grid.size(); ++y)
        for (int x = 0; x < grid[y].size(); ++x)
            if (grid[y][x] == '.') {
                int damage = dmgCalc(grid, x, y);
                if (damage > maxDamage) maxDamage = damage;
            }
    return (maxDamage * bombs >= getTargets(grid));
}

main() {
    vector<vector<char>>     grid, res;
    map<pair<int, int>, int> b;
    string                   tmp_in;

    int w, h; cin >> w >> h; cin.ignore();
    for (int i = 0; i < h && cin >> tmp_in; i++) {
        grid.push_back({});
        for (char c : tmp_in) grid.back().push_back(c);
    }
    res = grid;

    while (1) {
        int rounds, bombs; cin >> rounds >> bombs; cin.ignore();

        for(auto it = b.begin(); it != b.end();)
        {
            it->second--;
            if (it->second == 0) {
                dstroy(grid, it->first.first, it->first.second);
                it = b.erase(it);
            }
            else
                ++it;
        }

        int maxDamage = 0;
        Pos bombPos;
        for (int x = 0; x < w; ++x)
            for (int y = 0; y < h; ++y)
                if (res[y][x] == '.') {
                    int damage = dmgCalc(res, x, y);
                    if ((damage > maxDamage) && winnable(res, x, y, bombs-1)) { 
                        maxDamage = damage; bombPos = {x, y};
                    }
                }

        if (maxDamage == 0) { cout << "WAIT" << endl; continue; }
        
        if ((grid[bombPos.y][bombPos.x] == '.') && (b.find({bombPos.x, bombPos.y}) == b.end())) {
            dstroy(res, bombPos.x, bombPos.y);
            b[{bombPos.x, bombPos.y}] = 3;
            cout << bombPos.x << " " << bombPos.y << endl;
        }
        else cout << "WAIT" << endl;
    }
}