#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

int main() {
    int              N, val, maxS(0); 
    string           key, test;
    map<string, int> dic;

    cin >> N; cin.ignore();
    while ( N-- && cin >> key >> val ) 
    {
        dic[key] = val; cin.ignore();
        if ( maxS < key.size() ) { maxS = key.size(); }
    }
    cin >> test; cin.ignore();

    bool   isOk  (true);
    int    st_idx(0   ), cur_idx (-1  );
    string cur, res;
    while( isOk && ++cur_idx < test.length() )
    {
        cur += test.at(cur_idx);
        if      ( cur.size() > maxS            ) 
        { 
            isOk = false; 
        }
        else if ( dic.find( cur ) != dic.end() ) 
        { 
            res += (char)dic[cur];
            cur.clear();
            st_idx = cur_idx + 1;
        }
    }

    isOk = cur.empty();

    cout << ( isOk ? res : ("DECODE FAIL AT INDEX " + to_string(st_idx)) ) << endl;
}