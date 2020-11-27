#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;

bool isNb( const vector<int>& v ) 
{
    int len = accumulate(v.begin(), v.end(), 0);
    return ( !count_if(v.begin(), v.end(), [](int i){ return i < 0; }) && len )
    && ( (len == 1) || (len == 19 && v[0] == 18 && v[1] == 1) || (len < 19 && v[0] < len) );
}

string toNb( vector<int> v ) 
{
    string ret;
    v.resize(10, 0);

    for ( int i = 1; i < v.size(); ++i ) 
    {
        if ( v[i] ) 
        {
            --v[i];
            ret += (char)(i + '0');
            break;
        }
    }

    for ( int i = 0; i < v.size(); ++i ) 
    {
        for ( int j = 0; j < v[i]; ++j ) 
        {
            ret += (char)(i + '0');
        }
    }

    return ret;
}

bool test( vector<int>& a, const vector<int>& b ) 
{
    for (size_t i = 0; i < b.size(); ++i) 
    {
        a[i] -= b[i];
    }

    if (isNb(a)) 
    {
        return true;
    }

    for (size_t i = 0; i < b.size(); ++i) 
    {
        a[i] += b[i];
    }

    return false;
}

int main()
{
    string      s;
    vector<int> a(10, 0), b(10,0);
    
    cin >> s;
    
    for ( auto& c : s ) { ++a[c -'0']; }

    if ( test(a, {1}) ) 
    {
        cout << toNb({1}) << " " << toNb(a) << endl;
    } 
    else if (test(a, {18, 1})) 
    {
        cout << toNb(a) << " " << toNb({18, 1}) << endl;
    } 
    else 
    {
        int k    = 18;
        int last = -1;
        for (int i = 9; i >= 0; --i) 
        {
            int d = min(k, a[i]);
            if ( d > 0 && i > 0 ) 
            {
                last = i;
            }

            a[i] -= d;
            b[i] += d;
            k    -= d;
        }

        if ( !isNb(a) && last != -1 ) 
        {
            a[last] += 1;
            b[last] -= 1;

            if (a[0] > 0) 
            {
                a[0] -= 1;
                b[0] += 1;
            }
        }

        if (isNb(a) && isNb(b)) 
        {
            cout << toNb(a) << " " << toNb(b) << endl;
        } 
        else 
        {
            cout << -1 << " " << -1 << endl;
        }
    }

    return 0;
}