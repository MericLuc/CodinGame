#include <iostream>

using namespace std;

#define N 1000
int n, c[N][N], res[N], used[N];

int main() {
    cin >> n; cin.ignore();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n && cin >> c[i][j]; j++) { 
            if(++used[c[i][j]] > 1 || c[i][j] < 1 || c[i][j] > n*n ) { cout << "MUGGLE" << endl; exit(1); }
            res[i  ] += c[i][j]; 
            res[n+j] += c[i][j];
            if (i == j      ) res[2*n  ]+= c[i][j];
            if (i == (n-1-j)) res[2*n+1]+= c[i][j];
        }
    
    for (int i = 0; i < 2*n+2; i++) if (res[i] != res[0]) { cout << "MUGGLE" << endl; exit(1); }
    cout << "MAGIC" << endl;
}