#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main()
{
    vector<int> shots = vector<int>(4,0);
    int         n, res   = 0;

    cin >> n; cin.ignore();

    while ( shots[3] < 13 )
    {
        for ( int i = 0; i < 3; i++ )
            if ( shots[i] > 12 ) { shots[i] = 1; ++shots[i+1]; }
        
        if ( accumulate(shots.begin(), shots.end(), 0) == (50 - n) )
        {
            int ways = 1;
            for ( auto& it : shots )
                if ( it > 1 ) { ways *= 2; }
            
            res += ways;
        }

        ++shots[0];
    }

    cout << res << endl;
}

    /* 
     * Dynamic programming solution if we are not limited at 4 shots 
     */
    /*
    int n; cin >> n; cin.ignore();
    vector<int> res = vector<int>(51,0);
    res[50]         = 1;

    for ( int i = 49; i >= n; i-- )
    {
        res[i] = res[i+1];

        int tmp = 0;
        for ( int j = 2; j < 13; j++ )
        {
            if ( i + j > 50 ) { break; }
            tmp += res[i+j];
        }

        res[i] += 2 * tmp;
    }
    cout << res[n] << endl;
    */