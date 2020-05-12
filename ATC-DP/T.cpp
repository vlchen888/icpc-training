#include <bits/stdc++.h>

using namespace std;

int main() {
  // T: the idea is that dp[i][x] holds the number of
  // ways to form a permutation of (0, 1, ..., i-1) satisfying
  // the < and > constraints and ending with x.  Then future
  // states can be created by inserting into these permutations.
  //
  // Need prefix sums again to make it go fast enough

  cin.tie(0);
  cin.sync_with_stdio(0);

  int n; cin >> n;
  string s; cin >> s;
  long long MOD = 1e9+7;

  long long dp[n][n];
  for(int i = 0; i<n; ++i) {
    for(int j = 0; j<n; ++j) {
      dp[i][j] = 0;
    }
  }
  dp[0][0] = 1;
  for(int i = 1; i<n; ++i) {
    // Compute prefix sums
    long long pref[i+1];
    pref[0] = 0;
    for(int j = 0; j<i; ++j) {
      pref[j+1] = ((pref[j] + dp[i-1][j])%MOD + MOD) % MOD;
    }
    // So to get the sum from x to y of dp[i-1][j], you just
    // take dp[i-1][y+1] - dp[i-1][x]

    for(int x = 0; x<=i; ++x) {
      // suppose you've created 0 2 1 3, and are looking to
      // make the permutation go from 0 to 4 instead.
      // there's these 5 places to insert a number:
      //   0   1   2   3
      // |   |   |   |   |
      // and then shift the rest of the numbers over, forming
      // 1 3 2 4 0  (>)
      // 0 3 2 4 1  (>)
      // 0 3 1 4 2  (>)
      // 0 2 1 4 3  (>)
      // 0 2 1 3 4  (<)
      //
      // So > gets x to i-1, and < gets 0 to x-1
      if(s[i-1] == '<') {
        // dp[i][x] = sum of y from 0 to x-1 of dp[i-1][y]
        dp[i][x] = ((pref[x] - pref[0])%MOD + MOD) % MOD;
      }
      else {
        // dp[i][x] = sum of y from x to i-1 of dp[i-1][y]
        dp[i][x] = ((pref[i] - pref[x])%MOD + MOD) % MOD;
      }
    }
  }

  long long ret = 0;
  for(int i = 0; i<n; ++i) {
    ret = (ret + dp[n-1][i]) % MOD;
  }
  cout << ret << endl;
}
