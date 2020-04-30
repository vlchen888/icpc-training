#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  int n, k; cin >> n >> k;
  int h[n];
  for(int i = 0; i<n; ++i) cin >> h[i];

  vector<int> dp(n, INT_MAX);
  dp[0] = 0;
  for(int i = 0; i<n; ++i) {
    for(int j = 1; j<=k && i+j<n; ++j) {
      dp[i+j] = min(dp[i+j], dp[i]+abs(h[i] - h[i+j]));
    }
  }
  cout << dp[n-1] << endl;
}
