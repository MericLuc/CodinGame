#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cassert>

using namespace std;

static map<int, int> bin2digit = 
{
    { 126 , 0 }, // 1111110
    {  48 , 1 }, // 0110000
    { 109 , 2 }, // 1101101
    { 121 , 3 }, // 1111001
    {  51 , 4 }, // 0110011
    {  91 , 5 }, // 1011011
    {  95 , 6 }, // 1011111
    { 112 , 7 }, // 1110000
    { 127 , 8 }, // 1111111
    { 123 , 9 }  // 1111011
};

int util(char c, int i) { return ( c == ' ' ? 0 : 1 << i ); }

int main()
{
    vector<string> l(3, "");
    for ( int i = 0; i < 3             ; i++  ) { getline(cin, l[i]); }
    for ( int i = 0; i < l.at(0).size(); i+=3 )
    {
        int bin = util(l[0][i+1], 6 ) + 
                  util(l[1][i+2], 5 ) + util(l[1][i+1], 0 ) + util(l[1][i+0], 1 ) +
                  util(l[2][i+0], 2 ) + util(l[2][i+1], 3 ) + util(l[2][i+2], 4 );
        assert( bin2digit.find(bin) != bin2digit.end() );
        cout << bin2digit[bin];
    }
    cout << endl;
}