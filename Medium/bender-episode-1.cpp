#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define SOUTH 0
#define EAST 1
#define NORTH 2
#define WEST 3

vector<char> dirs = { SOUTH, EAST, NORTH, WEST };

typedef struct point_t {
    int x, y;
    inline bool operator==(const struct point_t& a) { return a.x == x and a.y == y; }
} Point;

/*std::ostream &operator<<(std::ostream &stream, Point const &p) // Debug, enable -> cerr << (Point);
{
    return stream << '{' << p.x << ',' << ' ' << p.y << '}';
}*/

char char2Dir(char c) 
{
    switch (c) {
        case 'N':
            return NORTH;
            break;
        case 'S':
            return SOUTH;
            break;
        case 'E':
            return EAST;
            break;
        case 'W':
            return WEST;
            break;
        default:
            cerr << "ERROR at char2Dir()" << endl;
    }   
}

void printDir(ostream& stream, char dir)
{
    switch (dir) {
        case NORTH:
            stream << "NORTH";
            break;
        case SOUTH:
            stream << "SOUTH";
            break;
        case EAST:
            stream << "EAST";
            break;
        case WEST:
            stream << "WEST";
            break;
        default:
            cerr << "ERROR at printDir()" << endl;
    }
    stream << '\n';
}

Point moveWithDir(Point p, char dir)
{
    switch (dir) {
        case NORTH:
            p.y--;
            break;
        case SOUTH:
            p.y++;
            break;
        case EAST:
            p.x++;
            break;
        case WEST:
            p.x--;
            break;
        default:
            cerr << "ERROR at moveWithDir()" << endl;
    }
    return p;
}

class Bender 
{
public:
    ~Bender();
    Bender();
    void setPos(Point p);
    void setMapSize(int _L, int _C);
    void setTP(int index, Point _p);
    int indexOfTP(Point _p);
    char move();
    void findNewDir();
    void processMove();
    bool positionBlocked(Point np);
    
    int L, C, TPNum; // Lines, Cols, Number of teleporters found
    Point p, lastP; // Bender point, last bender point
    char dirIndex;
    vector<vector<char>> map; // Map data
    vector<vector<char>> visited;
    Point tp[2]; // teleporters
    bool alive, breakerMode, dirReversed;
};

Bender::~Bender() {}
Bender::Bender() 
{
    TPNum = 0;
    alive = true;
    breakerMode = false;
    dirReversed = false;
}

void Bender::setPos(Point _p)
{
    p = _p;
}

void Bender::setMapSize(int _L, int _C)
{
    L = _L;
    C = _C;
    map = vector<vector<char>>(_L, vector<char>(_C));
    visited = vector<vector<char>>(_L, vector<char>(_C, 0));
    dirIndex = 0;
}

void Bender::setTP(int index, Point _p)
{
    tp[index] = _p;
}

int Bender::indexOfTP(Point _p)
{
    if (tp[0] == _p) return 0;
    if (tp[1] == _p) return 1;
    cerr << "ERROR at indexOfTP()" << endl;
}

char Bender::move()
{
    lastP = p;
    Point np = moveWithDir(p, dirs[dirIndex]);
    
    if (positionBlocked(np)) {
        findNewDir();
        return move(); // recurse with new dir
    }
    
    setPos(np);
    if (visited[p.y][p.x] > 5) return -1; // loop detected
    visited[p.y][p.x]++;
    // Reverse index if dir reversed
    char step = dirReversed ? 3 - dirIndex : dirIndex;
    processMove();
    
    return step;
}

void Bender::findNewDir()
{    
    for (dirIndex = 0; dirIndex < 4; dirIndex++) {
        Point np = moveWithDir(p, dirs[dirIndex]);
        if (!positionBlocked(np)) return;
    }   
}

bool Bender::positionBlocked(Point np)
{
    switch (map[np.y][np.x]) {
        case '#': return true;
        case 'X': return !breakerMode;
        default: return false;
    }
}

void Bender::processMove()
{
    char c = map[p.y][p.x]; // element at current pos (after move)
    
    switch (c) { 
        case '$':
            alive = false;
            return;
            
        case 'S':
        case 'E':
        case 'N':
        case 'W':
            // Reverse index if dir reversed
            dirIndex = dirReversed ? 3 - char2Dir(c) : char2Dir(c);
            return;
            
        case 'X':
            map[p.y][p.x] = ' '; // destroy obstacle
            return;
            
        case 'I':
            reverse(dirs.begin(), dirs.end());
            dirIndex = 3 - dirIndex; // Reverse dir
            dirReversed = !dirReversed;
            return;
            
        case 'B':
            breakerMode = !breakerMode;
            return;
            
        case 'T':
            p = tp[!indexOfTP(p)]; // set pos to the other teleporter
            return;
            
        default: return;
    }
}

int main()
{
    int L;
    int C;
    cin >> L >> C; cin.ignore();
    
    Bender b;
    b.setMapSize(L, C);
    
    for (int i = 0; i < L; i++) {
        string line;
        getline(cin, line);
        
        for (int j = 0; j < C; j++) {
            b.map[i][j] = line[j];
            switch (b.map[i][j]) {
                case '@':
                    b.map[i][j] = ' '; // clear position of player preventing errors
                    b.setPos({j, i});
                    break;
                    
                case 'T':
                    b.setTP(b.TPNum, {j, i});
                    b.TPNum++;
                    break;
                
                default: break;
            }
        }
    }
    
    bool loop = false;
    vector<char> moves;
    
    while (b.alive) {
        char move = b.move();
        
        if (move == -1) { // loop detected
            loop = true;
            break;
        }
        
        moves.push_back(move);
    }
    
    if (loop)
        cout << "LOOP\n";
    else
        for (int i = 0; i < moves.size(); i++) printDir(cout, moves[i]);
    
    cout << flush;
}