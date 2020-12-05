#include <iostream>
#include <vector>

using namespace std;

int                      N, t_A, t_B;
pair<int, int>           curr;
vector< pair<int, int> > dom;

void check() {
    if(dom.empty()) return;
    for( int i= 0; i < dom.size(); i++ ) {
        pair<int, int> t = dom[i];
        if ( curr.first  == t.first || curr.first  == t.second ||
             curr.second == t.first || curr.second == t.second ) { 
                 curr = t; 
                 dom.erase(dom.begin()+i); 
                 check(); 
        }
    }
}

int main() {
     cin >> N; cin.ignore();

    for (int i = 0; i < N && cin>>t_A>>t_B; i++) { dom.push_back( make_pair(t_A, t_B) ); }
    for (auto& i: dom) cerr << i.first << " : " << i.second << endl;
    curr = dom[0]; 
    dom.erase(dom.begin());
    check();
    cout << ( dom.empty() ? "true" : "false" )  << endl;
}