#include <bits/stdc++.h>

using namespace std;

int n;
vector<vector<int> > adj;
long long MOD = 1e9+7;

map<pair<int, bool>, long long> memo;
long long dp(int curr, bool is_black, int p) {
  if(memo.find(make_pair(curr, is_black)) != memo.end()) {
    return memo[make_pair(curr, is_black)];
  }
  long long ret = 1;
  for(int i = 0; i<adj[curr].size(); ++i) {
    int next = adj[curr][i];
    if(next == p) continue;
    if(is_black) {
      ret = (ret * dp(next, false, curr)) % MOD;
    }
    else {
      ret = (ret * (dp(next, false, curr) + dp(next, true, curr))) % MOD;
    }
  }
  memo[make_pair(curr, is_black)] = ret;
  return ret;
}

int main() {
  // P: a classic! tree DP 

  cin.tie(0);
  cin.sync_with_stdio(0);
  cin >> n;
  adj.resize(n);
  for(int i = 0; i<n-1; ++i) {
    int u, v; cin >> u >> v;
    u--; v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  cout << (dp(0, false, -1) + dp(0, true, -1)) % MOD << endl;
}
