#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void next(const vector<int>& arr, const int& d)  { 
    vector<int> a1, a2, a3, a4, res;
    int i = d-1,j = 0;
    while (arr[i] == 0         ) { a1.push_back(0);      i--; }
    if    (i >=0               ) { a2.push_back(arr[i]); i--; }
    if    (!a2.empty()         ) { a2[0]--;                   }
    while (i >=0 && arr[i] == 9) { a3.push_back(9);      i--; } 
    while (j <= i              ) { a4.push_back(arr[j]); j++; } 
    
    j = max(0, (int)a4.size()-1);
    if(a4.empty()) { a4.push_back(1); }
    else           { a4[j]++;         }

    for(auto c: a4  ) { res.push_back(c); }
    for(auto c: a1  ) { res.push_back(c); }
    for(auto c: a2  ) { res.push_back(c); }
    for(auto c: a3  ) { res.push_back(c); }
    for(auto c : res) { printf("%d", c);  }
} 

main() {
    long long   N; scanf("%lld", &N);
    int         d =0;
    vector<int> v_N;
    while(N) {
        v_N.insert(v_N.begin(), N%10);
        N /= 10; d++;
    }
    next(v_N, d);
}