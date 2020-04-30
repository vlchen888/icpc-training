#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  long long n, W; cin >> n >> W;
  long long w[n], v[n];
  for(long long i = 0; i<n; ++i) cin >> w[i] >> v[i];

  vector<long long> dp(100001, W+1);
  dp[0] = 0;
  long long ret = 0;
  for(long long i = 0; i<n; ++i) {
    for(long long j = 100000; j>=0; --j) {
      if(dp[j]+w[i] <= W) {
        dp[j+v[i]] = min(dp[j+v[i]], dp[j]+w[i]);
        ret = max(ret, j+v[i]);
      }
    }
  }

  cout << ret << endl;
}
