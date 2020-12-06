#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

string forward(const string& s)
{
    ostringstream r;
 
    for (size_t i = 0; i != s.length();) 
    {
        auto i2 = s.find_first_not_of(s[i], i + 1);
 
        if ( i2 == string::npos ) { i2 = s.length(); }
 
        r << i2 - i << s[i];
        i = i2;
    }
    
    return r.str();
}

bool backward(string& s)
{
    string s2;
    
    auto i1 = s.begin();
    auto i2 = i1 + 1;
    
    while ( i1 != s.end() && i2 != s.end() )
    {
        for(int i = 0; i < *i1-'0'; i++)
        {
            s2 += *i2;
        }
        i1 += 2;
        i2  = i1 + 1;
    }
        
    if      ( s.compare(forward(s2)) != 0 )                      { return true;       }
    else if ( ( s2.size() % 2 == 1 ) || ( s2.compare(s) == 0 ) ) {s = s2;return true; }
    
    s = s2;
    return false;
}

int main()
{
    string s;
    getline(cin, s);

    bool stop = false;
    while ( !stop )
    {
        stop = backward(s);
    }
    
    cout << s << endl;
}