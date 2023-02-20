#include <iostream>
using namespace std;

main() {
  int i_ind(0), n;
  bool i_str(false), i_line(true);
  cin >> n >> noskipws;

  for (char c; cin >> c; ) {
    if      ( i_str    ) { i_str = (c != '\''); cout << c; }
    else if ( c == '(' ) {
        if (!i_line) cout << endl;
        cout << string(i_ind, ' ') << c << endl;
        i_ind+= 4; i_line = true;
    }
    else if ( c == ')' ) {
        if (!i_line) cout << endl;
        i_ind-= 4; i_line = false;
        cout << string(i_ind, ' ') << c;
    }
    else if ( c == '\'' ) {
        cout << string(i_line * i_ind, ' ') << c;
        i_str = true; i_line = false;
    }
    else if ( c == ';'  ) { cout << c << endl; i_line = true; }
    else if (string(" \t\n").find(c) == string::npos) { cout << string(i_line * i_ind, ' ') << c; i_line = false; }
  }
}