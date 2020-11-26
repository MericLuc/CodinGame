#include <iostream>
#include <string>

using namespace std;

struct Sudoku
{
    static int MIN;
    static int MAX;
    
    int d[9][9];
    
    Sudoku() {}
    
    void addLine(const string& line, int i) {
        for ( int c = MIN; c < MAX; c++ ) { d[i][c] = line.at(c) - '0'; }
    }
    
    bool solve(void) {
        int r(0), c(0);
        if ( !findEmpty(r, c) )
            return true;
        for ( int i = 1; i < 10; i++ )
        {
            if ( isSafe(r, c, i) )
            {
                d[r][c] = i;
                if ( solve() )
                    return true;
                
                d[r][c] = 0;
            }
        }
        return false;
    }
    
    bool findEmpty(int& x, int& y) {
        for     ( x = MIN; x < MAX; x++ )
            for ( y = MIN; y < MAX; y++ )
                if ( d[x][y] == 0 ) 
                    return true; 
        
        return false;
    }
    
    bool isSafe  (int x, int y, int val) {
        for ( int i = MIN; i < MAX; i++ )
            if ( d[i][y] == val )
                return false;

        for ( int j = MIN; j < MAX; j++ )
            if ( d[x][j] == val )
                return false;

        for     ( int i = 3*(x/3); i < 3*(1 + x/3); i++ )
            for ( int j = 3*(y/3); j < 3*(1 + y/3); j++ )
                if ( d[i][j] == val )
                    return false;

        return true;
    }
    
    void print(void) const {
        for     ( int i = MIN; i < MAX; i++ )
        {
            for ( int j = MIN; j < MAX; j++ ) { cout << d[i][j]; }
            cout << endl;
        }
    }
};

int Sudoku::MIN = 0;
int Sudoku::MAX = 9;

int main() {
    string line;
    Sudoku game;
    
    for (int i = Sudoku::MIN; i < Sudoku::MAX; i++) 
    {
        getline(cin, line);
        game.addLine(line, i);
    }

    game.solve();
    game.print();
}