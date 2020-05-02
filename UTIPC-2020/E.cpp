#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair< int, int > pii;
typedef vector< int > vi;

vector<vi> adj;

int main() {
  int n, m;
  cin >> n >> m;
  adj.resize(n);
  for (int i = 0; i < m; i++) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  int p; cin >> p;
  vector<vector<double> > pol;
  vector<double> pr(n, 0);
  pol.push_back(pr);
  for(int i = 0; i<p; ++i) {
    int x; cin >> x;
    pol[0][x]++;
  }

  queue<pair<int, int> > q;
  map<pair<int, int>, double> dp;
  map<pair<int, int>, bool> seen;
  q.push(make_pair(0, 0));
  dp[make_pair(0, 0)] = 0;

  double ret = INT_MAX;
  while(!q.empty()) {
    pair<int, int> curr = q.front(); q.pop();

    if(seen[curr]) continue;
    seen[curr] = true;

    if(dp[curr] >= ret) continue;

    while(curr.second >= pol.size()-1) {
      vector<double> pn(n, 0);
      vector<double> pc = pol.back();
      for(int i = 0; i<n; ++i) {
        for(auto x : adj[i]) {
          pn[x] += 1.0/adj[i].size() * pc[i];
        }
      }
      pol.push_back(pn);
    }
    if(curr.first == n-1) {
      ret = min(ret, dp[curr]);
      continue;
    }

    for(auto x : adj[curr.first]) {
      if(dp.find(make_pair(x, curr.second+1)) == dp.end()) {
        dp[make_pair(x, curr.second+1)] = dp[curr] + pol[curr.second+1][x];
        q.push(make_pair(x, curr.second+1));
      }
      else if(dp[make_pair(x, curr.second+1)] > dp[curr] + pol[curr.second+1][x]) {
        dp[make_pair(x, curr.second+1)] = dp[curr] + pol[curr.second+1][x];
        q.push(make_pair(x, curr.second+1));
      }
    }
  }
  cout << fixed << setprecision(10) << ret << endl;
}
