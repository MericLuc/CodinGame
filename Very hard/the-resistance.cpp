#include <iostream>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

typedef long long ll;

struct Nodes 
{
    Nodes* dt    = nullptr;
    Nodes* ds    = nullptr;
    ll     valid = 0;
};

string encode(string input) {
    string res;
    for (auto& c : input)
    {
        switch (c)
        {
            case 'A': res += ".-"  ; break;
            case 'B': res += "-..."; break;
            case 'C': res += "-.-."; break;
            case 'D': res += "-.." ; break;
            case 'E': res += "."   ; break;
            case 'F': res += "..-."; break;
            case 'G': res += "--." ; break;
            case 'H': res += "...."; break;
            case 'I': res += ".."  ; break;
            case 'J': res += ".---"; break;
            case 'K': res += "-.-" ; break;
            case 'L': res += ".-.."; break;
            case 'M': res += "--"  ; break;
            case 'N': res += "-."  ; break;
            case 'O': res += "---" ; break;
            case 'P': res += ".--."; break;
            case 'Q': res += "--.-"; break;
            case 'R': res += ".-." ; break;
            case 'S': res += "..." ; break;
            case 'T': res += "-"   ; break;
            case 'U': res += "..-" ; break;
            case 'V': res += "...-"; break;
            case 'W': res += ".--" ; break;
            case 'X': res += "-..-"; break;
            case 'Y': res += "-.--"; break;
            case 'Z': res += "--.."; break;
        }
    }
    return res;
}

void insert(Nodes*    node, 
            string    wd, 
            long long pos = 0) {
    while ( pos < wd.size() ) 
    {
        if (wd[pos] == '.') 
        {
            if (!node->dt) node->dt = new Nodes();
            node = node->dt;
        }
        else 
        {
            if (!node->ds) node->ds = new Nodes();
            node = node->ds;
        }
        pos += 1;
    }
    node->valid++;
}

void deleteNodes(Nodes* node) {
    if (node->dt) deleteNodes(node->dt);
    if (node->ds) deleteNodes(node->ds);
    delete node;
}

string L, W;
Nodes* root = new Nodes();
map<ll, ll> cache;

ll solve(ll pos) {
    Nodes* node = root;
    ll solutions = 0;
    while (pos < L.size()) 
    {
        if      ( (L[pos] == '.') && node->dt ) { node = node->dt; }
        else if ( (L[pos] == '-') && node->ds ) { node = node->ds; }
        else break;
        
        if ( node->valid ) 
        {
            if (pos == L.size()-1) { solutions += node->valid; }
            else {
                if (cache.find(pos+1) != cache.end()) 
                {
                    solutions += node->valid *  cache[pos+1];
                }
                else 
                {
                    ll res = solve(pos+1);
                    if (res > 0) 
                    {
                        solutions += node->valid * res;
                        cache[pos+1] = res;
                    }
                }
            }
        }
        
        ++pos;
    }

    return solutions;
}

int main() {
    int N;
    cin >> L >> N; cin.ignore();
    
    for (int i = 0; i < N; i++)  
    {
        cin >> W; cin.ignore();
        insert(root, encode(W));
    }

    cout << solve(0) << endl;

    deleteNodes(root);
}