#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  int n; cin >> n;
  int h[n];
  for(int i = 0; i<n; ++i) cin >> h[i];

  vector<int> dp(n, INT_MAX);
  dp[0] = 0;
  for(int i = 0; i<n; ++i) {
    if(i != n-1) {
      dp[i+1] = min(dp[i+1], dp[i]+abs(h[i] - h[i+1]));
    }
    if(i != n-2) {
      dp[i+2] = min(dp[i+2], dp[i]+abs(h[i] - h[i+2]));
    }
  }
  cout << dp[n-1] << endl;
}
