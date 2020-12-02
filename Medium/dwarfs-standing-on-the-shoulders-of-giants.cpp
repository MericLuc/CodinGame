#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

set<int>                roots;
map< int, vector<int> > vertexes;

int countReferences(const int node)
{
    int l_res = 1; 
    if (vertexes[node].empty()) return l_res;
    else
    {
        for (int v : vertexes[node])
        {
            int c = countReferences(v);
            if (c > l_res) l_res = c;
        }
        return l_res + 1;
    }
}

int main()
{
    int  n;     // the number of relationships of influence
    int  x, y;  // a relationship of influence between two people (x influences y)
    int l_result(0);
    cin >> n; cin.ignore();
    
    for (int i = 0; i < n; i++) {
        cin >> x >> y; cin.ignore();
        
        roots.insert(x);
        vertexes[x].push_back(y);
    }
    
    for( const auto& it : vertexes ) 
        for( auto& dest : it.second ) roots.erase( dest );

    for (auto root : roots)
    {
        int c = countReferences(root);
        if (c > l_result) l_result = c;
    }
    
    cout << l_result << endl;
}