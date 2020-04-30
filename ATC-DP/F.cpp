#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  string s, t; cin >> s >> t;
  int n = s.length();
  int m = t.length();
  int dp[n+1][m+1];
  for(int i = 0; i<=n; ++i) {
    for(int j = 0; j<=m; ++j) {
      dp[i][j] = 0;
    }
  }
  for(int i = 0; i<n; ++i) {
    for(int j = 0; j<m; ++j) {
      if(s[i] == t[j]) {
        dp[i+1][j+1] = max(dp[i+1][j+1], dp[i][j]+1);
      }
      dp[i+1][j+1] = max(dp[i+1][j+1], dp[i+1][j]);
      dp[i+1][j+1] = max(dp[i+1][j+1], dp[i][j+1]);
    }
  }

  // Reconstruct answer
  int ci = n, cj = m;
  string ret = "";
  while(ci > 0 && cj > 0) {
    if(dp[ci][cj] == dp[ci-1][cj-1]+1 && s[ci-1] == t[cj-1]) {
      ret = s[ci-1] + ret;
      ci--;
      cj--;
    }
    else if(dp[ci][cj] == dp[ci-1][cj]) {
      ci--;
    }
    else {
      cj--;
    }
  }
  assert(ret.length() == dp[n][m]);
  cout << ret << endl;
}
