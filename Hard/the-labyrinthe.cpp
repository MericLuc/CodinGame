#include <bits/stdc++.h>

using namespace std;

#define N 0
#define S 1
#define E 2
#define W 3

static int R, C, A;

struct Point {
    int x, y;
    constexpr Point(int _x = -1, int _y = -1) noexcept : x{_x}, y{_y} {}
};

auto ptoi(const Point& p) noexcept { return C * p.y + p.x; }
auto itop(int n)          noexcept { return Point(n % C, n / C); }

auto operator==(const Point& a, const Point& b) { return a.x == b.x && a.y == b.y;    }
auto operator!=(const Point& a, const Point& b) { return a.x != b.x || a.y != b.y;    }
auto operator+ (const Point& a, const Point& b) { return Point(a.x + b.x, a.y + b.y); }
auto operator- (const Point& a, const Point& b) { return Point(a.x - b.x, a.y - b.y); }

const Point           null_point{-1, -1};
const array<Point, 4> dirs{{{0, -1}, {0, 1}, {1, 0}, {-1, 0}}};

char point_diff_to_dir(Point diff) 
{
    for (char i = 0; i < 4; i++)
        if (dirs[i] == diff) return i;
    return -1;
}

void reconstruct_path(
    stack<char>&             path,
    unordered_map<int, int>& from,
    Point                    cp
) {
    int last{ ptoi(cp) }, p{ last };
    while (from.find(p) != from.end()) {
        p = from[p];
        path.push(point_diff_to_dir(itop(p) - itop(last)));
        last = p;
    }
}

bool BFS_find(
    stack<char>& path,
    vector<vector<char>>& map,
    Point k,
    char target
) {
    unordered_set<int>      visited;
    unordered_map<int, int> from;
    queue<Point>            q;
    
    visited.insert(ptoi(k));
    q.push(k);
    
    while (!std::empty(q)) {
        Point cp{ q.front() };
        q.pop();
        
        for (int i = 0; i < 4; i++) {
            Point np{ cp + dirs[i] };
            
            if (visited.find(ptoi(np)) != visited.end())
                continue;
                
            if (map[np.y][np.x] == '#' || 
                (target != '?' && map[np.y][np.x] == '?'))
                continue;
            
            visited.insert(ptoi(np));
            from[ptoi(np)] = ptoi(cp);
            q.push(np);
            
            if (map[np.y][np.x] == target) {
                reconstruct_path(path, from, np);
                return true;
            }
        }
    }
    return false;
}
    
int main()
{
    cin >> R >> C >> A; cin.ignore();
    
    vector<vector<char>> map(R, vector<char>(C, '?'));
    Point _T{ null_point }, _C{ null_point };
    bool  C_reached{ false };
    
    while (1) {
        Point k;
        cin >> k.y >> k.x; cin.ignore();
        
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                char c;
                cin >> c;
                if (map[i][j] == '?')
                    map[i][j] = c;

                if (map[i][j] == 'T') _T = Point(j, i);
                if (map[i][j] == 'C') _C = Point(j, i);
            }
        }
        
        stack<char> path;
        
        if (k == _C)
            C_reached = true;
        
        if (path.empty()) {
            if (C_reached) {
                BFS_find(path, map, k, 'T');
            }
            else {
                if (_C == null_point)
                    BFS_find(path, map, k, '?');
                else if (!BFS_find(path, map, k, 'C'))
                    BFS_find(path, map, k, '?');
            }
        }
        
        switch (path.top()) {
            case S: cout << "UP"   << endl; break;
            case N: cout << "DOWN" << endl; break;
            case E: cout << "LEFT" << endl; break;
            case W: cout << "RIGHT" << endl; break;
        }
        path.pop();
    }
}