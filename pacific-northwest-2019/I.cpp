#include <bits/stdc++.h>

using namespace std;

vector<int> color;
vector<vector<int> > adj;
int col_z = 0, col_o = 0;

bool find(int j, vector<vector<int> > &g, vector<int> &btoa, vector<int> &vis) {
  if(btoa[j] == -1) return 1;
  vis[j] = 1; int di = btoa[j];
  for(auto e : g[di]) {
    if(!vis[e] && find(e, g, btoa, vis)) {
      btoa[e] = di;
      return 1;
    }
  }
  return 0;
}

int dfsMatching(vector<vector<int> > &g, vector<int> &btoa) {
  vector<int> vis;
  for(int i = 0; i<g.size(); ++i) {
    vis.assign(btoa.size(), 0);
    for(auto j : g[i]) {
      if(find(j, g, btoa, vis)) {
        btoa[j] = i;
        break;
      }
    }
  }
  return btoa.size() - (int)count(btoa.begin(), btoa.end(), -1);
}

void dfs(int curr) {
  for(int i = 0; i<adj[curr].size(); ++i) {
    if(color[adj[curr][i]] == -1) {
      color[adj[curr][i]] = 1-color[curr];
      if(color[adj[curr][i]] == 0) col_z++;
      else col_o++;
      dfs(adj[curr][i]);
    }
  }
}

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);
  int n; cin >> n;

  map<string, int> mp;
  vector<string> ss(n);
  for(int i = 0; i<n; ++i) {
    string s; cin >> s;
    mp[s] = i;
    ss[i] = s;
  }

  color.assign(n, -1);
  adj.resize(n);
  for(int i = 0; i<n; ++i) {
    string s = ss[i];
    for(int j = 0; j<s.length(); ++j) {
      for(int k = j+1; k<s.length(); ++k) {
        swap(s[j], s[k]);
        if(mp.find(s) != mp.end()) {
          adj[i].push_back(mp[s]);
        }
        swap(s[j], s[k]);
      }
    }
  }

  for(int i = 0; i<n; ++i) {
    if(color[i] == -1) {
      color[i] = 0;
      dfs(i);
    }
  }

  map<int, pair<int, bool> > colormap;
  int lc = 0, rc = 0;
  for(int i = 0; i<n; ++i) {
    if(color[i] == 0) {
      colormap[i] = make_pair(lc++, false);
    }
    else {
      colormap[i] = make_pair(rc++, true);
    }
  }
  vector<vector<int> > adj2(lc);
  for(int i = 0; i<n; ++i) {
    if(color[i] == 0) {
      for(int j = 0; j<adj[i].size(); ++j) {
        adj2[colormap[i].first].push_back(colormap[adj[i][j]].first);
      }
    }
  }

  vector<int> btoa(rc, -1);

  int ret = n - dfsMatching(adj2, btoa);

  cout << ret << endl;
}
