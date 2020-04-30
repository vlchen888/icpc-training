#include <bits/stdc++.h>

using namespace std;

int main() {
  // O: looks like just a n^2*2^n bitmask DP
  // n*2^n states: dp[i][ii] = processed the first i men,
  // ii is bitmask of women left unpaired
  // n transitions
 
  cin.tie(0);
  cin.sync_with_stdio(0);
  int n; cin >> n;
  vector<vector<int> > adj(n);
  for(int i = 0; i<n; ++i) {
    for(int j = 0; j<n; ++j) {
      int is_pair; cin >> is_pair;
      if(is_pair == 1) {
        adj[i].push_back(j);
      }
    }
  }

  long long MOD = 1e9+7;
  vector<long long> dp(1<<n, 0), dpnext(1<<n, 0);
  dp[0] = 1;
  for(int i = 0; i<n; ++i) {
    dpnext.assign(1<<n, 0);
    for(int j = 0; j<(1<<n); ++j) {
      if(dp[j] == -1) continue;
      for(int l = 0; l<adj[i].size(); ++l) {
        // for all possible pairings for i...
        int k = adj[i][l];
        if((j >> k) & 1) {
          // make sure they're not already taken
          continue;
        }
        dpnext[j+(1<<k)] = (dpnext[j+(1<<k)] + dp[j]) % MOD;
      }
    }
    swap(dp, dpnext);
  }
  cout << dp[(1<<n) - 1] << endl;
}
