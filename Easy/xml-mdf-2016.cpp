#include <iostream>
#include <string>
#include <map>

using namespace std;

main() {
    string str; getline(cin, str);
    float c_depth(0), res_val(0); char res_c;
    map< char, float > weights;

    for ( auto it = str.begin(); it != str.end(); it++ )
        if   ( *it == '-' ) { c_depth--; it++;                      }
        else                { c_depth++; weights[*it] += 1/c_depth; }

    for ( auto c : weights )
        if (( c.second > res_val ) || (( c.second == res_val ) && (c.first < res_c)) ) { res_val = c.second; res_c = c.first; }
    cout << res_c << endl;
}