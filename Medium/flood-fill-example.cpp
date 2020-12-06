#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define S_MAX 30

struct Game
{
    int w, h;
    int t;
    int ID;
    bool end;
    
    char data[S_MAX][S_MAX];
    char tmp [S_MAX][S_MAX];
    int  time[S_MAX][S_MAX];
    int  id  [S_MAX][S_MAX];
    
    Game(int W=0, int H=0):w(W), h(H), t(1), ID(0), end(false) {}
    
    void addLine(const string& line, int i)
    {
        for ( int j = 0; j < line.size(); j++ )
        {
            data[i][j] = line.at(j);
            time[i][j] = ( line.at(j) == '.' ||  line.at(j) == '#' ) ? 0 : t;
            id  [i][j] = ( line.at(j) == '.' ||  line.at(j) == '#' ) ? 0 : ++ID;
        }
    }
    
    void printState(void) const
    {
        for     ( int i = 0; i<h; i++ )
        {
            for ( int j = 0; j<w; j++ )
            {
                cout << data[i][j];
            }
            cout << endl;
        }
    }
    
    void printId   (void) const
    {
        for     ( int i = 0; i<h; i++ )
        {
            for ( int j = 0; j<w; j++ )
            {
                cerr << id[i][j];
            }
            cerr << endl;
        }
    }
    
    void printTime(void) const
    {
        for     ( int i = 0; i<h; i++ )
        {
            for ( int j = 0; j<w; j++ )
            {
                cerr << time[i][j];
            }
            cerr << endl;
        }
    }
    
    void solve(void)
    {
        while ( !end )
        {
            diffuse();
        }
    }
    
    void diffuse(void)
    {
        createTemp();
        end = true;
        ++t;
        for     ( int i = 0; i<h; i++ )
        {
            for ( int j = 0; j<w; j++ )
            {
                char c = data[i][j];
                int  k = id  [i][j];
                if ( Game::isTroop(c) )
                {
                    // Propagate North
                    if ( i > 0  ) propagate(i - 1 , j    , c, k);
                    
                    // Propagate South
                    if ( i < h-1) propagate(i + 1 , j    , c, k);

                    
                    // Propagate West
                    if ( j > 0  ) propagate(i     , j - 1, c, k);

                    // Propagate East
                    if ( j < w-1) propagate(i     , j + 1, c, k);
                }
            }
        }
        
        updateData();
    }
    
    void propagate ( int i, int j, char c, int k)
    {
        if ( data[i][j] != '#' )
        {
        
            if      ( time[i][j] == 0 ) 
            {
                time[i][j] = t;
                id  [i][j] = k;
                tmp [i][j] = c;
                end        = false;
            } 
            else if ( time[i][j] == t ) 
            {
                if ( id[i][j] != k )
                {
                    tmp [i][j] = '+';
                    id  [i][j] = -1 ;
                    end        = false;
                }
            }
        }
    }
    
    void createTemp(void)
    {
        for     ( int i = 0; i<h; i++ )
            for ( int j = 0; j<w; j++ )
            {
                tmp[i][j] = data[i][j];
            }
    }
    
    void updateData (void)
    {
        for     ( int i = 0; i<h; i++ )
            for ( int j = 0; j<w; j++ )
            {
                data[i][j] = tmp[i][j];
            }
    }
    
    static bool isTroop(char c)
    {
        return ( (c != '.') && (c != '#') );
    }
};

int main()
{
    string line;
    int    width,   height;
    cin >> width >> height; cin.ignore();

    Game   game(width, height);
    for ( int i = 0; i < height; i++ ) 
    {
        getline(cin, line);
        game.addLine(line, i);
    }

    game.solve     ();
    game.printState();
}