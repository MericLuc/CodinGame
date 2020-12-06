#include <iostream>
#include <string>
#include <vector>

using namespace std;

void test_empty(vector<string>& data) {
    if ( !data.empty() ) {
        cout << data[0];
        for ( int i = 1; i < data.size(); i++ ) { cout << " > " << data[i]; }
        cout << endl;
    }
}

int main() {
    int            pts, n; cin >> n; cin.ignore();
    vector<string> stack;
    string         tmp;
    
    for (int i = 0; i < n && getline(cin, tmp); i++) {
        pts = tmp.rfind(".");
        pts = (pts == string::npos) ? 0 : ++pts;
        
        if( pts >= stack.size() ) { stack.push_back( tmp.substr(pts) ); }
        else {
            test_empty(stack);
            stack.erase( stack.begin()+pts, stack.end() );
            stack.push_back( tmp.substr(pts) );
        }
    }
    test_empty(stack);
}