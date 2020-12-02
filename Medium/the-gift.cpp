#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int N, C, total_budget(0);
    int average;
    int l_return;
    cin >> N; cin.ignore();
    cin >> C; cin.ignore();
    vector<int> budgets(N, 0);
    
    for (int i = 0; i < N; i++) { cin >> budgets[i]; cin.ignore(); total_budget += budgets[i]; }
    
    sort( budgets.begin(), budgets.end() );
    if ( total_budget < C )  cout << "IMPOSSIBLE" << endl;
    else
    {  
        int i = 0;
        for ( auto ood : budgets )
        {
            average = C / (N - i);
            l_return = (ood >= average) ? average : ood;
            cout << l_return << endl;
            C -= l_return;
            i++;
        }
    }
}