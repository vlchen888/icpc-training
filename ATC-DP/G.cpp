#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<int> > out, in;
vector<int> dep;

int dfs(int curr) {
  if(dep[curr] != -1) return dep[curr];

  int ret = 0;
  for(int i = 0; i<out[curr].size(); ++i) {
    int v = out[curr][i];
    ret = max(ret, 1+dfs(v));
  }

  dep[curr] = ret;
  return ret;
}

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  cin >> n >> m;
  out.resize(n);
  in.resize(n);
  dep.assign(n, -1);
  for(int i = 0; i<m; ++i) {
    int u, v; cin >> u >> v;
    u--; v--;
    out[u].push_back(v);
    in[v].push_back(u);
  }


  int ret = 0;
  for(int i = 0; i<n; ++i) {
    if(in[i].size() == 0) {
      ret = max(ret, dfs(i));
    }
  }
  cout << ret << endl;
}
