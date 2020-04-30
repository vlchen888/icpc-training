#include <bits/stdc++.h>

using namespace std;

int n;
long long MOD = 1e9+7;
typedef vector<vector<long long> > vll;
vll mult(vll a, vll b) {
  vll ret(n, vector<long long>(n, 0));
  for(int i = 0; i<n; ++i) {
    for(int j = 0; j<n; ++j) {
      for(int k = 0; k<n; ++k) {
        ret[i][j] = (ret[i][j] + a[i][k] * b[k][j]) % MOD;
      }
    }
  }
  return ret;
}

int main() {
  // R: I know that you can just take the adjacency matrix
  // and raise it to the power K to get a matrix with the
  // number of paths from i to j, so the answer would be
  // the sum of all of the elements of A^K
  //
  // which means some fun matrix exponentiation, I guess...
  // it's like N^3 per square, and there's <100 squares involved
  // so it should totally fit in time
  // just pretty gross to code...

  cin.tie(0);
  cin.sync_with_stdio(0);
  cin >> n;
  long long k; cin >> k;
  vector<vector<long long> > a(n, vector<long long>(n)), r(n, vector<long long>(n));
  for(int i = 0; i<n; ++i) {
    for(int j = 0; j<n; ++j) {
      cin >> a[i][j];
      r[i][j] = 0;
    }
    r[i][i] = 1;
  }

  while(k) {
    if(k % 2) {
      r = mult(a, r);
    }
    a = mult(a, a);
    k /= 2;
  }
  long long ret = 0;
  for(int i = 0; i<n; ++i) {
    for(int j = 0; j<n; ++j) {
      ret = (ret + r[i][j]) % MOD;
    }
  }
  cout << ret << endl;
}
