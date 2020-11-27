#include <bits/stdc++.h>
using namespace std;

int main() {
    int           N;        /*!< Total number of transactions       */
    string        tr;       /*!< transaction string                 */
    vector<float> nbs(9,0); /*!< Number of tr starting with digit i */
    vector<float> law =
    { 30.1, 17.6, 12.5, 9.7, 7.9, 6.7, 5.8, 5.1, 4.6 };
    
    cin >> N; cin.ignore();

    for ( int i = 0; i < N; i++ )
    {
        getline(cin, tr);
        std::size_t pos = tr.find_first_of("123456789");
        ++nbs[ tr[pos] - '0' - 1 ];
    }

    string l_ret("false");
    for ( auto& nb : nbs ) 
    { 
        nb /= 0.01*N; 
        nb = abs(nb - law[&nb - &nbs[0]]);

        if ( nb > 10 ) { l_ret = "true"; break; }
    }
    cout << l_ret << endl;
}