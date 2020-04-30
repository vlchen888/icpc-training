#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  long long n, W; cin >> n >> W;
  long long w[n], v[n];
  for(long long i = 0; i<n; ++i) cin >> w[i] >> v[i];

  vector<long long> dp(W+1, 0);
  set<long long> poss;
  poss.insert(0);
  long long ret = 0;
  for(long long i = 0; i<n; ++i) {
    set<long long> next = poss;
    auto it = poss.end();
    while(it != poss.begin()) {
      it--;
      long long ddpp = dp[*it];
      if(*it+w[i] <= W) {
        dp[*it+w[i]] = max(dp[*it+w[i]], ddpp+v[i]);
        ret = max(ret, dp[*it+w[i]]);
        next.insert(*it+w[i]);
      }
    }
    
    poss = next;
  }

  cout << ret << endl;
}
