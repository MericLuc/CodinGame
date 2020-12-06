#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h> 

using namespace std;

/*------------ Defines -----------*/
#define DEBUG 0

/*------- Types definition -------*/
typedef long long LONG;

static void Dbg(const string& msg) { if ( DEBUG ) { cerr << msg << endl; } }

struct Rational
{
    LONG x, y;
    
    Rational(LONG px=1, LONG py=1):
        x(px), y(py)
        {}
    
    Rational(string& s)
    {
        auto pos = s.find('/');
        if ( pos != string::npos )
        {
            x = stoll(s, &pos , 0);
            s = s.substr(pos+1);
            y = stoll(s, &pos, 0);
            
            Rational::simplify(this);
            
            Dbg("String in the form a/q");
            printDbg();
            
            toDirections();
        }
        else
        {
            x = 1;
            y = 1;
            
            Rational Pl(0,1), Pr(1,0);
            
            // TODO - convertir à la volée
            for( const auto& c : s )
            {
                if ( c == 'R' )
                {
                    Pl     = *this;
                    *this += Pr;                   
                }
                else
                {
                    Pr     = *this;
                    *this += Pl;                    
                }
                Rational::simplify(this);
            }
            toString();
        }
    }
    
    Rational& operator=(const Rational& r)
    {
        x = r.x;
        y = r.y;
        
        return *this;
    }
    
    Rational& operator+=(const Rational& r)
    {
        x += r.x;
        y += r.y;
        
        return *this;
    }
    
    bool operator==(const Rational& r)
    {
        return (r.x == x && r.y == y);
    }
    
    bool operator!=(const Rational& r)
    {
        return !(*this == r);
    }
    
    bool operator>(const Rational& r)
    {
        LONG l_y1 = (y   == 0) ? 1 : y  ;
        LONG l_y2 = (r.y == 0) ? 1 : r.y;
        return ( static_cast<double>(x)/l_y1 > static_cast<double>(r.x)/l_y2 );
    }
    
    static void simplify(Rational* r) 
    {
        if ( r == nullptr ) { return; }
        
        auto d = __gcd(r->x, r->y); 
        r->x /= d;  
        r->y /= d;  
    }
    
    void printDbg(void) const { if ( DEBUG ) { cerr << x << "/" << y << endl; } }
    
    void toString(void) const { cout << x << "/" << y << endl; }
    
    void toDirections(void)
    {
        string res = "";
        Rational Pl(0,1), Pr(1,0), Pc(1,1);
        
        while ( *this != Pc )
        {
            if ( *this > Pc )
            {
                Pl   = Pc;
                Pc  += Pr;
                res += "R";
            }
            else
            {
                Pr   = Pc;
                Pc  += Pl;
                res += "L";
            }

            Rational::simplify(&Pc);
        }
        
        cout << res << endl;
    }
};

int main()
{
    string line;
    int    tests;
    cin >> tests; cin.ignore();
    
    for (int i = 0; i < tests; i++) 
    {
        getline(cin, line);
        Rational r(line);
    }
}