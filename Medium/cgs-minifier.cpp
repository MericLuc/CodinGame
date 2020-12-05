#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

string in, out, tmp;
char repl = '`';

int main() {
    map<string, char> repl_map;
    int    N; cin >> N; cin.ignore();
    for (int i = 0; i < N && getline(cin, tmp); i++) { in += tmp; }
    for (int i = 0; i < in.size(); i++) {
        char c = in[i];
        if      ( c == '$'  )  { 
            string t;
            out.push_back(c);
            do { i++; t.push_back(in[i]); } while( in[i] != '$' );
            if(repl_map.find(t) == repl_map.end()) {repl_map[t] = ++repl;}
            out.push_back(repl_map[t]);
            out.push_back(c);
        }
        else if ( c == '\'' )  { 
            out.push_back(c);
            do { i++; out.push_back(in[i]); } while( in[i] != '\'' );
        }
        else                   {
            switch(in[i]) {
                case ' ' : case '\t': case '\n': break;
                default  : out.push_back(in[i]); break;
            }
        }
    }
    cout << out << endl;
}

