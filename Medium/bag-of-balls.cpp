#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

typedef long long int lld;

void getFactors (lld num, vector<lld>& vec) {
  if (num != 1) { vec.push_back(num); }
  for (int i = 2; i <= sqrt( static_cast<double>(num) ); i++)
    if (num%i == 0) { vec.push_back(i); vec.push_back(num/i); }
}

void simplifyFun(lld& a, lld& b) {
  lld tempN = a, tempD = b, small, temp;
  vector<long long int> vec;
  if      (tempN == tempD ) { a = 1;  b = 1; return ; }
  else if (tempN == -tempD) { a = -1; b = 1; return ; }
  else if (tempN == 0     ) { b = 1;         return ; }

  small = (abs(tempN) < abs(tempD)) ? abs(tempN) : abs(tempD);

  getFactors(small, vec);
  for (int i = 0; i < vec.size(); i++) {
    temp = vec[i];
    while (tempN%temp == 0 && tempD%temp == 0) { tempN /= temp; tempD /= temp; }
  }
  a = tempN; b = tempD;
}

lld bin( int n, int k) {
  n -= k; double c = 1;
  for (int i = 1; i <= k; i++) { c = c * (n + i) / i; }
  return c;
}

main() {
    int N, W, s, k;
    cin >> N >> W >> s >> k; cin.ignore();
    
    lld a = (bin(W,k) * bin(N-W, s-k)), b = bin(N,s);
    simplifyFun(a, b);
    if ( a == b ) cout << "1:0" << endl;
    else          cout << a << ":" << (b - a) << endl;
}