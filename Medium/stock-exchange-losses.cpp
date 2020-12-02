#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n, l_result(0), next_local_min_index(0);
    
    cin >> n; cin.ignore();
    vector<int> values(n,0);
    for (auto i = 0; i < n; i++) { cin >> values[i]; cin.ignore(); }

    vector<int>::iterator result = values.begin();
    for (auto it = values.begin(); it < values.end(); ++it )
    {
        if( next_local_min_index <= distance(begin(values), it) ) 
        {
            result               = min_element(it, end(values));
            next_local_min_index = distance(begin(values), result);
        }
        
        int return_val = *result - *it;
        
        if( *it > *result && abs(return_val) > abs(l_result) ) l_result = return_val;
    }
    
    cout << l_result << endl;
}