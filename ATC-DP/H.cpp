#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  long long MOD = 1e9+7;
  int h, w; cin >> h >> w;
  string grid[h];
  for(int i = 0; i<h; ++i) {
    cin >> grid[i];
  }

  long long dp[h][w];
  for(int i = 0; i<h; ++i) {
    for(int j = 0; j<w; ++j) {
      dp[i][j] = 0;
    }
  }
  dp[0][0] = 1;
  for(int i = 0; i<h; ++i) {
    for(int j = 0; j<w; ++j) {
      if(grid[i][j] == '#') continue;
      if(i != 0) dp[i][j] += dp[i-1][j];
      if(j != 0) dp[i][j] += dp[i][j-1];
      dp[i][j] = dp[i][j] % MOD;
    }
  }
  cout << dp[h-1][w-1] << endl;
}
