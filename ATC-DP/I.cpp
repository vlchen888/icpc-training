#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  int n; cin >> n;
  double p[n];
  for(int i = 0; i<n; ++i) {
    cin >> p[i];
  }

  // dp[i] represents the probability that after x rolls,
  // there are i heads
  vector<double> dp(n+1, 0), dpswap(n+1);
  dp[0] = 1-p[0];
  dp[1] = p[0];

  for(int x = 1; x<n; ++x) {
    dpswap.assign(n+1, 0);

    for(int i = 0; i<n; ++i) {
      dpswap[i] += dp[i] * (1-p[x]);
      dpswap[i+1] += dp[i] * (p[x]);
    }

    swap(dp, dpswap);
  }

  double ret = 0;
  for(int i = (n+1)/2; i<=n; ++i) {
    ret += dp[i];
  }
  cout << fixed << setprecision(10) << ret << endl;
}
