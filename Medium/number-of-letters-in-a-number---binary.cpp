#include <iostream>
using namespace std;

void next ( long long& x ) {
    long long tmp = x; x = 0;
    while (tmp > 0) { x += 4 - tmp % 2; tmp /= 2; }
}

main() {
    long long start, checker, n; cin >> start >> n; cin.ignore();
    while ( n-- && (checker != start) ) { checker = start; next(start); }
    cout << start << endl;
}