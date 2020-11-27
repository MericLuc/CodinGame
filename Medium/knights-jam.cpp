#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>

using namespace std;

typedef enum
{
    OOB  = -9,
    ST_8 = -8,
    ST_7 = -7,
    ST_6 = -6,
    ST_5 = -5,
    ST_4 = -4,
    ST_3 = -3,
    ST_2 = -2,
    ST_1 = -1,
    FREE = 9
} CELL_STATE;

map<CELL_STATE, char> toChar = {
    {OOB,'X'} , {ST_8,'8'}, {ST_7,'7'}, {ST_6, '6'},
    {ST_5,'5'}, {ST_4,'4'}, {ST_3,'3'}, {ST_2, '2'},
    {ST_1,'1'}, {FREE,'.'}
                               };

typedef pair<int,int> Cell;

struct Board 
{
    CELL_STATE grid[7][7];
    Cell freePos;

    Board()
    {
        for     ( int i = 0; i < 7; i++ )
        {
            for ( int j = 0; j < 7; j++ )
            {
                grid[i][j] = OOB;
            }            
        }

        string line;
        for     ( int i = 0; i < 3; i++ )
        {
            getline(cin, line);
            for ( int j = 0; j < 3; j++ )
            {
                grid[i+2][j+2] = ( line[j] == '.' ) ? FREE : static_cast<CELL_STATE>(-(line[j]-'0'));

                if ( line[j] == '.' ) { freePos = Cell(i+2,j+2); }
            }
        }
    }

    bool isComplete(void) const
    {
        static Cell endFreePos = Cell(4,4);

        if ( freePos != endFreePos ) { return false; }
        for     ( int i = 0; i < 3; i++ )
        {
            for ( int j = 0; j < 3; j++ )
            {
                if ( abs(grid[i+2][j+2]) != (i*3+j+1) ) 
                { 
                    return false; 
                }
            }
        }
        return true;
    }

    vector<Cell> moves( int i, int j )
    {
        vector<Cell> ret;
        ret.reserve(8);

        if ( grid[i-2][j-1]>0 ) { ret.push_back( Cell(i-2,j-1) ); }
        if ( grid[i-2][j+1]>0 ) { ret.push_back( Cell(i-2,j+1) ); }
        if ( grid[i-1][j-2]>0 ) { ret.push_back( Cell(i-1,j-2) ); }
        if ( grid[i-1][j+2]>0 ) { ret.push_back( Cell(i-1,j+2) ); }
        if ( grid[i+1][j-2]>0 ) { ret.push_back( Cell(i+1,j-2) ); }
        if ( grid[i+1][j+2]>0 ) { ret.push_back( Cell(i+1,j+2) ); }
        if ( grid[i+2][j-1]>0 ) { ret.push_back( Cell(i+2,j-1) ); }
        if ( grid[i+2][j+1]>0 ) { ret.push_back( Cell(i+2,j+1) ); }

        return ret;
    }

    vector<Cell> moves( Cell& c )
    {
        return moves(c.first, c.second );
    }

    vector<Cell> movesB( Cell& c )
    {
        vector<Cell> ret;
        ret.reserve(8);

        int i = c.first;
        int j = c.second;

        if ( grid[i-2][j-1] != OOB ) { ret.push_back( Cell(i-2,j-1) ); }
        if ( grid[i-2][j+1] != OOB ) { ret.push_back( Cell(i-2,j+1) ); }
        if ( grid[i-1][j-2] != OOB ) { ret.push_back( Cell(i-1,j-2) ); }
        if ( grid[i-1][j+2] != OOB ) { ret.push_back( Cell(i-1,j+2) ); }
        if ( grid[i+1][j-2] != OOB ) { ret.push_back( Cell(i+1,j-2) ); }
        if ( grid[i+1][j+2] != OOB ) { ret.push_back( Cell(i+1,j+2) ); }
        if ( grid[i+2][j-1] != OOB ) { ret.push_back( Cell(i+2,j-1) ); }
        if ( grid[i+2][j+1] != OOB ) { ret.push_back( Cell(i+2,j+1) ); }

        return ret;
    }

    void exchange(Cell& src, Cell& dst)
    {
        CELL_STATE tmp = grid[src.first][src.second];

        grid[src.first][src.second] = grid[dst.first][dst.second];
        grid[dst.first][dst.second] = tmp;
    }

    void solveBck(Cell src, int& num)
    {
        Cell forbidden = freePos;
        exchange(src, freePos);
        freePos = src;
        num++;

        print();
        if ( !isComplete() && num < 30 )
        {
            auto cd = movesB(freePos);
            if ( cd[0] != forbidden )
            {
                solveBck(cd[0], num);
            }
            else
            {
                solveBck(cd[1], num);
            }
        }
    }

    int solve(void) 
    {
        int num1 = 0;
        int num2 = 0;

        CELL_STATE cpy[7][7];
        Cell cpyFree = freePos;
        for ( int i = 0; i < 7; i++ )
        {
            for ( int j = 0; j < 7; j++ )
            {
                cpy[i][j] = grid[i][j];
            }
        }

        if ( grid[3][3] != ST_5 ) { return -1; }

        if ( !isComplete() )
        {
            auto cd = movesB(freePos);
            solveBck(cd[0], num1);
            for ( int i = 0; i < 7; i++ )
            {
                for ( int j = 0; j < 7; j++ )
                {
                    grid[i][j] = cpy[i][j];
                    freePos = cpyFree;
                }
            }
            solveBck(cd[1], num2);
        }

        int r = min(num1, num2);
        
        return r < 30 ? r : -1;
    }

    void print(void) const
    {
        cerr << "\t-----\n";
        for     ( int i = 0; i < 3; i++ )
        {
            cerr << "\t";
            for ( int j = 0; j < 3; j++ )
            {
                cerr << toChar[grid[i+2][j+2]] << " ";
            }
            cerr << endl;
        }
    }
};

int main()
{
    Board b;
    
    cout << b.solve() << endl;
}