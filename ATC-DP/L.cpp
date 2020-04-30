#include <bits/stdc++.h>

using namespace std;

long long n;
vector<long long> a;
long long dp[3002][3002];

long long go(long long i, long long j) {
  if(dp[i][j] != -1) return dp[i][j];

  if(i+j == n) {
    // base case
    return 0;
  }
  if((i+j) % 2 == 0) {
    // it's Taro's turn, he is trying to maximize
    long long take_left  = a[i] + go(i+1, j);
    long long take_right = a[n-j-1] + go(i, j+1);
    dp[i][j] = max(take_left, take_right);
    return dp[i][j];
  }
  else {
    // it's Jiro's turn, he is trying to minimize
    long long take_left  = -a[i] + go(i+1, j);
    long long take_right = -a[n-j-1] + go(i, j+1);
    dp[i][j] = min(take_left, take_right);
    return dp[i][j];
  }
}

int main() {
  // L: right now, just looking like a straightforward n^2
  // DP, where dp[i][j] is the state after taking i from
  // the left and j from the right
  // and you can tell whose turn it is by the parity
  // of i+j

  cin.tie(0);
  cin.sync_with_stdio(0);

  cin >> n;
  a.resize(n);
  for(long long i = 0; i<n; ++i) {
    cin >> a[i];
  }
  for(long long i = 0; i<=3000; ++i) {
    for(long long j = 0; j<=3000; ++j) {
      dp[i][j] = -1;
    }
  }

  cout << go(0, 0) << endl;
}
