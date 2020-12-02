#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;
map<char, int> values { { 'I', 1 }, { 'V', 5 }, { 'X', 10 },  { 'L', 50 }, { 'C', 100 }, { 'D', 500 }, { 'M', 1000 } };

int toArabic(const string& p_str) {
    int l_return = 0;
    for (auto c = p_str.begin(); c < p_str.end()-1; ++c )
        if      ( *c == 'I' ) l_return += ( *(c+1) == 'V' || *(c+1) == 'X' ) ? -values[*c] : values[*c];
        else if ( *c == 'X' ) l_return += ( *(c+1) == 'L' || *(c+1) == 'C' ) ? -values[*c] : values[*c];
        else if ( *c == 'C' ) l_return += ( *(c+1) == 'D' || *(c+1) == 'M' ) ? -values[*c] : values[*c];
        else                  l_return += values[*c];
    l_return += values[*(p_str.end()-1)];
    return l_return;
}

void toRoman(int p_int) {
    int   bases[]  = {1000,900,500, 400,100, 90,  50, 40,  10,  9,   5,  4,  1 }; 
    char *symbol[] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};    
    int   i        =  0;
    while(p_int) {
        while(p_int/bases[i]) { cout<< symbol[i]; p_int -= bases[i]; }
        i++;
    }
}

main() {
    string a, b; cin >> a >> b; cin.ignore();
    toRoman( toArabic(a) + toArabic(b) );
}