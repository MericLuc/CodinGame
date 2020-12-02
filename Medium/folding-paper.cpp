#include <iostream>
#include <string>
#include <map>

using namespace std;

main() {
    map< char, int >    x { {'R',     1}, {'L',     1}, {'U',     1}, {'D',     1} };
    map< char, string > y { {'R', "LUD"}, {'L', "RUD"}, {'U', "DLR"}, {'D', "ULR"} };
    string order, side; getline(cin, order); getline(cin, side);
    for ( auto c : order ) { x[ y[c][0] ] += x[c]; x[ y[c][1] ] *= 2; x[ y[c][2] ] *= 2; x[c] = 1; }
    cout << x[side[0]] << endl;
}