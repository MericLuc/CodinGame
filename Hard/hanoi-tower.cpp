#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <math.h>

using namespace std;

struct Game
{
    typedef vector<int> Axe;
    typedef vector<Axe> Axes;
    
    int  N;
    Axes axes;
    map<int, int> idx;
    
    Game(int n=1): 
    N(n),
    axes(Axes()),
    idx(map<int, int>())
    {
        for ( int i = 0; i < 3; i++)
        {
            axes.emplace_back(Axe());
            axes[i].reserve(N);
        }
        
        for ( int i = N; i > 0; i-- )
        {
            axes[0].push_back(i);
        }   
        
        idx[0] = N;
        idx[1] = 3*N + 2;
        idx[2] = 5*N + 4;
    }
    
    void compute(int t)
    {
        do
        {
            for ( int i = 0; i < 3; i++ )
            {
                if ( axes[i][axes[i].size()-1] == 1 )
                {
                    int l  = ( i     == 0 ) ? 2 : i-1;
                    int r  = ( i     == 2 ) ? 0 : i+1;
                    int ch = ( N % 2 == 0 ) ? l : r  ;
                    
                    axes[i ].pop_back ( );
                    if ( N % 2 == 0 ) 
                    {
                        axes[r].push_back(1);
                    }
                    else
                    {
                        axes[l].push_back(1);
                    }
                    
                    if ( --t )
                    {
                        if      ( axes[i].empty() )
                        {
                            axes[i ].push_back( axes[ch].back() );
                            axes[ch].pop_back();
                        }
                        else if ( axes[ch].empty() )
                        {
                            axes[ch].push_back(axes[i].back());
                            axes[i ].pop_back();
                        }
                        else if ( axes[i].back() < axes[ch].back() )
                        {
                            axes[ch].push_back( axes[i].back() );
                            axes[i ].pop_back();
                        }
                        else
                        {
                            axes[i ].push_back( axes[ch].back() );
                            axes[ch].pop_back();
                        }
                        --t;
                    }
                    
                    break;
                }
            }
        } while ( t ); 
    }
    
    void printDbg(void) const
    {
        for ( int i = 0; i < 3; i++ )
        {
            for ( const auto& it : axes[i] ) { cout << it << " "; }
            cout << endl;
        }
    }
    
    void print(void) const
    {
        for ( int i = N-1; i >= 0; i-- )
        {
            // Create basic design
            string cur(3 * (2*N+1) + 2, ' ');
            
            for(int j = 0; j < 3; j++)
            {
                cur[ idx.at(j) ] = '|';
            }
            
            // Add the disks
            for ( int j = 0; j < 3; j++ )
            {
                if ( axes[j].size() > i )
                {
                    int l = axes[j][i];
                    for ( int k = idx.at(j) - l; k <= idx.at(j) + l; k++ )
                    {
                        cur[k] = '#';
                    }
                }
            }
            
            // Trim the string
            cur.erase(std::find_if(cur.rbegin(), 
                                   cur.rend  (), 
                                   [](int ch) { return !std::isspace(ch);}).base(), 
                      cur.end());
    
            cout << cur << endl;
        }
    }
};

int main()
{
    int    disks,   turn;
    cin >> disks >> turn; cin.ignore();

    Game game(disks);
    game.compute(turn);
    
    game.print();
    
    cout << pow(2, disks) -1 << endl;
}