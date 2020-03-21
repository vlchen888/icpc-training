#include <bits/stdc++.h>

using namespace std;

int main() {
  // Write out the first few terms:
  //
  // 42
  // 11k + 77
  // 32k + 112
  // 63k + 147
  // 104k + 182
  // ...
  //
  // Notice that the integer term is always divisible by 7.  Factoring that out:
  //
  // 0k + 6*7
  // 11k + 11*7
  // 32k + 16*7
  // 63k + 21*7
  // 104k + 26*7
  // ...
  //
  // Each k term is divisible by the non-7 number the integer term is:
  //
  // 6*0k + 6*7
  // 11*1k + 11*7
  // 16*2k + 16*7
  // 21*3k + 21*7
  // 26*4k + 26*7
  // ...
  //
  // Factor:
  //
  // 6(0k + 7)
  // 11(1k + 7)
  // 16(2k + 7)
  // ...
  //
  // The ith term is (5i+6)(ki + 7) if we use 0-indexing.
  // So both of these terms need to be prime, since neither of them can be 1.
  //
  // Since n is <= 1000000, and these terms are bounded by 100*n+7, we can just run a sieve and check all of the possible terms.


  int k, n; cin >> k >> n;

  vector<bool> is_prime(100*n+8, true);
  is_prime[0] = false;
  is_prime[1] = false;
  for(int i = 2; i<is_prime.size(); ++i) {
    if(is_prime[i]) {
      for(int j = 2; i*j<is_prime.size(); ++j) {
        is_prime[i*j] = false;
      }
    }
  }


  if(k % 2 == 1) cout << 0 << endl;
  else {
    int ret = 0;
    for(int i = 0; i<n; ++i) {
      int L = 5*i+6;
      int R = k*i+7;
      if(is_prime[L] && is_prime[R]) ret++;
    }
    cout << ret << endl;
  }
}
