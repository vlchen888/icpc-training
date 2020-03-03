#include <bits/stdc++.h>

using namespace std;

int main() {
  int n, m; cin >> n >> m;

  string grid[n];
  for(int i = 0; i<n; ++i) {
    cin >> grid[i];
  }

  int dp[n][m];
  for(int i = 0; i<n; ++i) {
    for(int j = 0; j<m; ++j) {
      dp[i][j] = 1;
    }
  }

  int mx = 1;
  for(int i = 1; i<n; ++i) {
    for(int j = 1; j<m; ++j) {
      int candidate = min(dp[i-1][j], dp[i][j-1]);
      if(grid[i-candidate][j-candidate] == grid[i-candidate][j-candidate+1] && grid[i][j] == grid[i][j-1]) {
        dp[i][j] = candidate+1;
      }
      else if(grid[i][j] == grid[i][j-1]) {
        dp[i][j] = candidate;
      }
      else {
        dp[i][j] = 1;
      }
      mx = max(mx, dp[i][j]);
      //cout << i << " " << j << " " << dp[i][j] << endl;
    }
    //cout << endl;
  }
  cout << mx*mx << endl;
}
