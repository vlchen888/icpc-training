#include <bits/stdc++.h>

using namespace std;

int main() {
  // M: dp[i][j] is the number of ways to distribute
  // candies to the first i kids (1-idx) with j candies left over
  
  cin.tie(0);
  cin.sync_with_stdio(0);

  long long n, k; cin >> n >> k;
  long long a[n];
  for(int i = 0; i<n; ++i) {
    cin >> a[i];
  }
  long long MOD = 1e9+7;
  long long dp[n+1][k+1];
  for(int i = 0; i<=n; ++i) {
    for(int j = 0; j<=k; ++j) {
      dp[i][j] = 0;
    }
  }

  dp[0][k] = 1;

  for(int i = 0; i<n; ++i) {
    vector<int> dpsums(k+2, 0);
    for(int j = 0; j<=k; ++j) {
      dpsums[j+1] = (dpsums[j] + dp[i][j]) % MOD;
    }
    for(int j = 0; j<=k; ++j) {
      // wait a minute... this is too slow!
      // there's nk states, but a[i] transitions,
      // so it's O(n*k^2), which is way TLEing
      //
      // like imagine you've gone through the first i kids
      // and have some dp state
      // j   = 0, 1, 2, 3, 4, 5, ...
      // dp  = a, b, c, d, e, f, ...
      // so we want the next dp state to be
      // dp' = a+b+c+d+e+f+..., b+c+d+e+f+..., ...
      // which you can do with prefix sums I guess
      dp[i+1][j] = (dpsums[min(k, j+a[i])+1] - dpsums[j] + MOD) % MOD;
      // bleh
    }
  }

  cout << dp[n][0] << endl;
}
