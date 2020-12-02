#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <algorithm>
#include <numeric>

using namespace std;

int main()
{
    string line;
    int M; cin >> M; cin.ignore();
    vector<int> temps;
    float N60_mean = 0.f, N8_mean = 0.f;

    for (int i = 0; i < M; i++) 
    {
        getline(cin, line);
        istringstream iss(line);
        for(string s; iss >> s; ) 
        { 
            temps.push_back(stoi(s)); 
        }
    }
    
    int i = 0;
    do {
        auto it = temps.begin() + i;
        N60_mean += 10 + (accumulate( it, it + 15, 0) - 40)/7.f;
        i += 15;
    } while( i + 15 <= temps.size() );
    
    i = 0;
    int j = 0;
    do {
        j++;
        auto it = temps.begin() + i;
        N8_mean += 5 + accumulate( it, it + 2, 0);
        i += 2;
    } while( i + 2 <= temps.size() );
        
    N60_mean/=M; 
    N8_mean /=j;
    
    cout << fixed << setprecision(1) << (float)N60_mean << endl;
    if( N60_mean >= 5 && N60_mean <= 30 ) 
    { 
        cout << fixed << setprecision(1) << N8_mean << endl; 
    }
}