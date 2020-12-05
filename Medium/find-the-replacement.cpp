#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    map<char,char> dic;
    string X, Y, Z; getline(cin, X); getline(cin, Y);

    if      ( !X.compare(Y) )                      { cout << "NONE" << endl; return 0;      }
    else for( int c = 0;  c < X.size(); c++ ) {
            if     ( dic.find(X[c]) == dic.end() ) { dic[X[c]] = Y[c]; Z.push_back(X[c]);   }
            else if( dic[X[c]] != Y[c]           ) { cout << "CAN'T" << endl; return 0;     }
    }
    for(auto i:Z) { if( i != dic[i]) cout << i << "->" << dic[i] << endl; }
}