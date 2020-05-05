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

  // O(n^2 2^n) is too slow!  We need O(n 2^n) instead
  vector<pair<int, int> > stateorder;
  for(int i = 0; i<(1<<n); ++i) {
    stateorder.push_back(make_pair(__builtin_popcount(i), i));
  }
  sort(stateorder.begin(), stateorder.end());

  long long MOD = 1e9+7;
  vector<long long> dp(1<<n, 0);
  dp[0] = 1;
  for(int jj = 0; jj<(1<<n)-1; ++jj) {
    int i = stateorder[jj].first;
    int j = stateorder[jj].second;
    for(int l = 0; l<adj[i].size(); ++l) {
      // for all possible pairings for i...
      int k = adj[i][l];
      if((j >> k) & 1) {
        // make sure they're not already taken
        continue;
      }
      dp[j+(1<<k)] = (dp[j+(1<<k)] + dp[j]) % MOD;
    }
  }
  cout << dp[(1<<n) - 1] << endl;
}
