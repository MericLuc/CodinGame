#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

#define DEBUG 0

using namespace std;

struct Card {
    unsigned value;
    char     color;
        
    Card(const string& p_input)
    {
        if(p_input.size() == 3)
        {
            value  = 10;
            color  = p_input[2];
        }
        else
        {
            if( isdigit(p_input[0]) ) value = p_input[0] - 48;
            else {
                switch(p_input[0])
                {
                    case 'J': value = 11; break;
                    case 'Q': value = 12; break;
                    case 'K': value = 13; break;
                    case 'A': value = 14; break;
                    default:  value = 15; break;
                }
            }
            color = p_input[1];
        }
    }
    
    Card(const Card& p_other)
    {
        value = p_other.value;
        color = p_other.color;
    }
    
    bool operator<(const Card& p_other)
    {
        if( DEBUG && value < p_other.value)
            cerr << "(" << value << " < " << p_other.value << ")" << endl;
        return (value < p_other.value);
    }
    
    bool operator>(const Card& p_other)
    {
        if( DEBUG && value > p_other.value)
            cerr << "(" << value << " > " << p_other.value << ")" << endl;
        return (value > p_other.value);
    }
};
    
ostream& operator << (ostream &out, const Card &c)
{
    return (out << "(" << c.value << "," << c.color << ")" << endl);
}

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{  
    int n;          // the number of cards for player 1
    int m;          // the number of cards for player 2
    int turns = 0;  // number of turns in the game
    
    list<Card> p1, p2;               // Cards of each players
    list<Card> p1_battle, p2_battle; // Cards curently in the battle
    
    cin >> n; cin.ignore();
    for (int i = 0; i < n; i++) 
    {
        string cardp1; // the n cards of player 1
        cin >> cardp1; cin.ignore();
        
        // Add card to player stack
        p1.push_back(Card(cardp1));
    }
 
    cin >> m; cin.ignore();
    for (int i = 0; i < m; i++) 
    {
        string cardp2; // the m cards of player 2
        cin >> cardp2; cin.ignore();

        // Add card to player stack
        p2.push_back(Card(cardp2));
    }
    
    if(DEBUG)
    {
        cerr << " -- p1 cards -- " << endl;
        for(list<Card>::iterator it = p1.begin(); it != p1.end(); ++it) cerr << *it;
        cerr << " -- p2 cards -- " << endl;
        for(list<Card>::iterator it = p2.begin(); it != p2.end(); ++it) cerr << *it;
         cerr << " ------------- " << endl;
    }
    
    while(1)
    {   
        if( p1_battle.empty() )
            ++turns;
            
        p1_battle.push_back(p1.front());
        p2_battle.push_back(p2.front());
        
        p1.pop_front();
        p2.pop_front();
        
        if( p1_battle.back() < p2_battle.back() )         // p2 wins the battle
        {
            p2.splice(p2.end(),p1_battle);
            p2.splice(p2.end(),p2_battle);
            
            if( p1.empty() )
            {
                cout << 2 << " " << turns << endl;
                break;
            }
        }
        else if( p1_battle.back() > p2_battle.back() )    // p1 wins the battle
        {
            p1.splice(p1.end(),p1_battle);
            p1.splice(p1.end(),p2_battle);
            
            if( p2.empty() )
            {
                cout << 1 << " " << turns << endl;
                break;
            }
        }
        else                // battle
        {
            if(DEBUG) cerr << "Battle!" << endl;
            if ( p1.size() < 4 || p2.size() < 4 )
            {
                cout << "PAT" << endl;
                break;
            }
            
            for(int i=0; i<3; ++i)
            {
                p1_battle.push_back( p1.front() );
                p1.pop_front();
                
                p2_battle.push_back( p2.front() );
                p2.pop_front();
            }
        }
    }
}