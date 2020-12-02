#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <list>

using namespace std;

map<char, list<char> > wins  = {
                    { 'R', {'L', 'C'}  },
                    { 'P', {'R', 'S'}  },
                    { 'C', {'L', 'P'}  },
                    { 'L', {'S', 'P'}  },
                    { 'S', {'C', 'R'}  } 
                    };

struct Player
{
    Player(int p_num = 0,
           char p_sign = ' ') :
           num   (p_num        ),
           sign  (p_sign       ),
           rounds(vector<int>())
           {}
           
    bool operator< (Player& p2)
    {
        rounds.push_back(p2.num);
        p2.rounds.push_back(num);
        
        if      ( find(wins[sign].begin(),
                       wins[sign].end  (),
                       p2.sign) != wins[sign].end() )
        {
            return true;
        }
        else if ( find(wins[p2.sign].begin(),
                       wins[p2.sign].end  (),
                       sign) != wins[p2.sign].end() )
        {
            return false;
        }
        else
        {
            return ( num < p2.num );
        }
    }
           
    int         num;
    char        sign;
    vector<int> rounds;
};

int main()
{
    int              N, num;
    string           sign;
    vector< Player > contestants;
    
    cin >> N; cin.ignore();
    contestants.reserve(N);
    
    for (int i = 0; i < N; i++) 
    {
        cin >> num >> sign; cin.ignore();
        contestants.emplace_back( Player(num, sign[0]) );
    }
    
    while ( contestants.size() > 1 )
    {
        vector< Player > current;
        
        for ( int i = 0; i < contestants.size()-1; i+=2 )
        {
            Player&  p1  = contestants.at(i  );
            Player&  p2  = contestants.at(i+1);
            
            if ( p1 < p2 ) { current.push_back(p1); }
            else           { current.push_back(p2); }
        }
        
        contestants = current;
    }

    const Player& winner = contestants.at(0);
    cout << winner.num << endl;
    for( int i = 0; i < winner.rounds.size()-1; i++ )
    {
        cout << winner.rounds.at(i) << " ";
    }
    cout << winner.rounds.at(winner.rounds.size()-1) << endl;
}