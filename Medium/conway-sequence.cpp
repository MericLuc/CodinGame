#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> Conwait_it(vector<int>& p_data)
{
    vector<int> l_return;
    for (auto it = p_data.begin(); it != p_data.end(); )
    {
        int l_cmpt = 0;
        for (auto it2 = it; it2 != p_data.end(); ++it2)
        {
            if(*it2 == *it) ++l_cmpt;
            else break;
        }
        l_return.push_back(l_cmpt);
        l_return.push_back(*it);
        it += l_cmpt;
    }
    return l_return;
}

int main()
{
    int R, L;
    cin >> R; cin.ignore();
    cin >> L; cin.ignore();
    vector<int> result(1, R);
    
    for(auto i = 0; i<L-1; ++i) result = Conwait_it(result);
    for(auto i = 0; i < result.size()-1; ++i) cout << result[i] << " ";
    cout << result[result.size() -1] << endl;
}