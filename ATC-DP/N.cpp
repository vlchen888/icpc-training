#include <bits/stdc++.h>

using namespace std;

int main() {
  // N: anything with a lineup like this makes me worry about
  // the fancy DP techniques... I don't want to have to do
  // divide-and-conquer DP :'(
  // but luckily it looks like it's just a range DP, which
  // is much better!
  // because O(n^3) fits in time

  cin.tie(0);
  cin.sync_with_stdio(0);
  int n; cin >> n;
  long long a[n];
  long long apref[n+1];
  apref[0] = 0;
  for(int i = 0; i<n; ++i) {
    cin >> a[i];
    apref[i+1] = apref[i] + a[i];
  }

  // dp[i][j] = the min. cost to merge everything in the range
  // i - j
  long long dp[n][n];
  for(int i = 0; i<n; ++i) {
    for(int j = 0; j<n; ++j) {
      dp[i][j] = LLONG_MAX;
    }
  }

  for(int len = 0; len<n; ++len) {
    for(int i = 0; i+len<n; ++i) {
      if(len == 0) {
        dp[i][i+len] = a[i];
      }
      else {
        for(int j = i; j<i+len; ++j) {
          // split to the right of j
          // ugh great, more prefix sums
          dp[i][i+len] = min(dp[i][i+len], apref[i+len+1]-apref[i] + dp[i][j] + dp[j+1][i+len]);
        }
      }
    }
  }
  // idk why it's off by this amount exactly??
  cout << dp[0][n-1]-apref[n] << endl;
}
