#include <bits/stdc++.h>

using namespace std;

long long m;

long long inv(long long x) {
  long long xc = x;
  long long ret = 1;
  long long pow = m-2;
  while(pow) {
    if(pow & 1) {
      ret = (ret * x) % m;
    }
    x = (x * x) % m;
    pow /= 2;
  }
  //assert((xc * ret) % m == 1);
  return ret;
}

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  long long v, x; cin >> v >> x >> m;
  
  for(long long p = 1; p<m; ++p) {
    long long q = inv((v * inv(p)) % m);
    //cout << p << " " << q << " " << inv(q) << endl;
    //assert((p * inv(q))%m == v);
    if(p - q*x >= 0 && p-q*x<q) {
      cout << p << " " << q << endl;
      return 0;
    }
  }
  cout << -1 << endl;
}
