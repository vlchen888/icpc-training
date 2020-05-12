#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
long long MOD = 1e9+7, LIM = 3e5;
vector<ll> fact(LIM), invfact(LIM);
long long ncr(long long n, long long c) {
  return (((fact[n] * invfact[c]) % MOD) * invfact[n-c]) % MOD;
}

ll inv(ll x) {
  ll x_b = x;
  ll ret = 1;
  ll pow = MOD - 2;
  while(pow) {
    if(pow % 2 == 1) ret = (ret * x) % MOD;
    x = (x * x) % MOD;
    pow /= 2;
  }
  assert((x_b * ret) % MOD == 1);
  return ret;
}

int main() {
  // Y: dp[i][j] (where grid[i][j] is a wall) is the number
  // of ways to get from (i, j) to (H, W) without passing
  // through any other walls on the way there.  It turns out
  // that dp[i][j] = #ways to get from (i, j) to (H, W) without
  // walls - sum over all walls that could be in the way of
  // the path (#ways to get from (i, j) to wall * dp[wall])
  cin.tie(0);
  cin.sync_with_stdio(0);
  
  // I love combinatorics in O(1) with moduli
  ll* inv = new ll[LIM] - 1; inv[1] = 1;
  for(int i = 2; i<LIM; ++i)
    inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;

  fact[0] = 1;
  fact[1] = 1;
  invfact[0] = 1;
  invfact[1] = 1;
  for(int i = 2; i<LIM; ++i) {
    fact[i] = (fact[i-1] * i) % MOD;
    invfact[i] = (invfact[i-1] * inv[i]) % MOD;
  }

  int H, W, n; cin >> H >> W >> n;
  vector<pair<int, int> > walls(n);
  for(int i = 0; i<n; ++i) {
    cin >> walls[i].first >> walls[i].second;
  }
  pair<int, int> tl = {1, 1};
  walls.push_back(tl);

  sort(walls.rbegin(), walls.rend());
  long long dp[walls.size()];
  for(int i = 0; i<(int)walls.size(); ++i) {
    // Combinatorics: paths from (a, b) to (H, W) is the number
    // of paths with (H-a) downs and (W-b) rights, so the
    // number of ways is (H-a+W-b) choose (W-b).
    int a = walls[i].first;
    int b = walls[i].second;
    dp[i] = ncr(H-a+W-b, W-b);

    for(int j = 0; j<i; ++j) {
      // Due to the sort, only walls with index <i can block
      // wall i's path to the end
      if(walls[j].first >= walls[i].first && walls[j].second >= walls[i].second) {
        int c = walls[j].first;
        int d = walls[j].second;
        dp[i] = ((dp[i] - (dp[j] * ncr(c-a+d-b, d-b))%MOD)+MOD)%MOD;
      }
    }
  }

  cout << dp[walls.size()-1] << endl;
}
