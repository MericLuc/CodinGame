#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>

#define DEBUG 0     // Display debug infos
#define TYPES 14    // Number of pieces types

using namespace std;

struct Piece
{
    int x;   // X pos
    int y;   // Y pos
    int type;// type
    
    Piece(const int p_x,
          const int p_y,
          const int p_type): x(p_x), y(p_y), type(p_type)
          {};
    
    // Output when enters from RIGHT
    void r(void) const 
    {
        switch(type)
        {
            case 1:  cout << x   << " " << y+1 << endl; break;
            case 2:  cout << x-1 << " " << y   << endl; break;
            case 4:  cout << x   << " " << y+1 << endl; break;
            case 6:  cout << x-1 << " " << y   << endl; break;
            case 7:  cout << x   << " " << y+1 << endl; break;
            case 8:  cout << x   << " " << y+1 << endl; break;
            case 12: cout << x   << " " << y+1 << endl; break;
            default: break;
        }
    }
    
    // Output when enters from LEFT
    void l(void) const
    {
        switch(type)
        {
            case 1: cout << x   << " " << y+1 << endl; break;
            case 2: cout << x+1 << " " << y   << endl; break;
            case 5: cout << x   << " " << y+1 << endl; break;
            case 6: cout << x+1 << " " << y   << endl; break;
            case 8: cout << x   << " " << y+1 << endl; break;
            case 9: cout << x   << " " << y+1 << endl; break;
            case 13:cout << x   << " " << y+1 << endl; break;
            default: break;
        }
    }
    
    // Output when enters from TOP
    void t(void) const 
    {
        switch(type)
        {
            case 1: cout << x   << " " << y+1 << endl; break;
            case 3: cout << x   << " " << y+1 << endl; break;
            case 4: cout << x-1 << " " << y   << endl; break;
            case 5: cout << x+1 << " " << y   << endl; break;
            case 7: cout << x   << " " << y+1 << endl; break;
            case 9: cout << x   << " " << y+1 << endl; break;
            case 10:cout << x-1 << " " << y   << endl; break;
            case 11:cout << x+1 << " " << y   << endl; break;
            default: break;
        }
    } 
    
    // Output wherever you come from
    void out(const int p_from) const 
    {
        switch(p_from)
        {
            case 0: r(); break;
            case 1: l(); break;
            case 2: t(); break;
            default:r(); break;
        }
    }
};

ostream& operator<<(ostream& os, const Piece& p_current)
{
    return ( os << "T" << p_current.type << ":X" 
                << p_current.x << ":Y" << p_current.y << endl );
}

int main()
{
    int W, H;
    cin >> W >> H; cin.ignore();
    vector< Piece > array;
    map<string, int> moves;
    moves["RIGHT"] = 0; moves["LEFT"] = 1; moves["TOP"] = 2;
    
    for (int i = 0; i < H; i++) 
    {
        string LINE; 
        getline(cin, LINE);

        istringstream iss(LINE);
        string s;
        int cmpt = 0;
        while ( getline( iss, s, ' ' ) )
        {
            int tmp_type = atoi(s.c_str());
            array.push_back(Piece(cmpt++, i, tmp_type));
            
            if(DEBUG) cerr << " " << s; 
        }
        if(DEBUG) cerr << endl;
    }
    
    if(DEBUG) 
        std::for_each(std::begin(array), 
                      std::end  (array), [](Piece& it){ cerr << it; } );
    
    int EX; cin >> EX; cin.ignore();

    // game loop
    while (1) {
        int XI, YI; 
        string POS;
        cin >> XI >> YI >> POS; cin.ignore();

        array[YI*W + XI].out(moves[POS]);
    }
}