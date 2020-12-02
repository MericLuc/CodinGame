#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <queue>
#include <cassert>

using namespace std;
 
struct POS 
{ 
    int          x, y;
    int          dist;
    bool         access;
    bool         vis;
    vector<POS*> neighbours;

    POS() : x(-1), y(-1), dist(0), access(true), vis(false) {}

    bool valid (void) const   { return ( x >= 0 && y >= 0 && x < 10 && y < 10 ); }
    bool acces (void) const   { return access; }
    void setPos(int u, int v) { x = u; y = v;  }
};

bool operator== ( const POS& a, const POS& b)
{
    return ( (a.x == b.x) && (a.y == b.y) );
}

bool valid(int x, int y) { return ((x >= 0 && y >= 0) && 
                                   (x < 10 && y < 10) ); }

typedef vector<POS>  ROW;

void init( vector< ROW >& grid )
{
    for ( int i = 0; i < grid.size(); i++ )
    {
        for ( int j = 0; j < grid[i].size(); j++ )
        {
            POS* l_curPos = &grid[i][j];
            l_curPos->setPos(i,j);

            if ( valid(i-1,j  ) ) { l_curPos->neighbours.push_back(&grid[i-1][j  ]); }
            if ( valid(i+1,j  ) ) { l_curPos->neighbours.push_back(&grid[i+1][j  ]); }
            if ( valid(i  ,j-1) ) { l_curPos->neighbours.push_back(&grid[i  ][j-1]); }
            if ( valid(i  ,j+1) ) { l_curPos->neighbours.push_back(&grid[i  ][j+1]); }
        }
    }
}

int BFS( POS* src, 
         POS* dst, 
         vector< ROW >& grid )
{
    assert(src && dst   && "Source or dest is not set!");
    assert(src->valid() && "Source is invalid!"        );
    assert(dst->valid() && "Dest is invalid!"          );

    src->vis = true;

    queue<POS*> q;
    q.push(src);

    while( !q.empty() )
    {
        POS* curPos = q.front();

        if ( *curPos == *dst )
        {
            return curPos->dist;
        }

        q.pop();

        for ( auto& l_nhb : curPos->neighbours )
        {
            if ( l_nhb->valid() && 
                 l_nhb->acces() && 
                 !l_nhb->vis )
            {
                l_nhb->vis  = true;
                l_nhb->dist = curPos->dist + 10;

                q.push(l_nhb);
            }
        }
    }

    return 0;
}

int main()
{
    vector< ROW > grid(10, ROW(10, POS()) );
    POS*          strPos = nullptr;
    POS*          endPos = nullptr;

    for (int i = 0; i < 10; i++) 
    {
        string row;
        getline(cin, row);

        for ( int j = 0; j < row.size(); j++ )
        {
            switch ( row.at(j) )
            {
                case '#': grid[i][j].access = false; break;
                case 'M': endPos = &grid[i][j];      break;
                case 'C': strPos = &grid[i][j];      break;
                default : break;
            }
        }
    }
    init(grid);

    cout << BFS(strPos, endPos, grid) << "km" << endl;
}