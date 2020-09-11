#include <bits/stdc++.h>

using namespace std;

struct edge {
  int to;
  int color;
};

int n;
vector<vector<edge> > adj;

vector<int> good;
bool dfs(int curr, int parent, bool killed) {
  bool ret = false; // becomes true if we discover something lethal to the dfs after this node

  set<int> colors, bad_colors;
  for(int i = 0; i<adj[curr].size(); ++i) {
    edge e = adj[curr][i];
    if(colors.find(e.color) != colors.end()) {
      bad_colors.insert(e.color);
    }
    colors.insert(e.color);
  }
  for(int i = 0; i<adj[curr].size(); ++i) {
    edge e = adj[curr][i];
    if(bad_colors.find(e.color) != bad_colors.end()) {
      if(e.to == parent) {
        good.clear(); // kill dfs nodes traversed earlier
        ret = true; // kill dfs nodes traversed later
      }
    }
  }
  for(int i = 0; i<adj[curr].size(); ++i) {
    edge e = adj[curr][i];
    if(bad_colors.find(e.color) != bad_colors.end()) {
      if(e.to == parent) {
        // already done above
      }
      else {
        // if we find an upwards kill in this subtree, propagate it up?
        bool result = dfs(e.to, curr, true);
        if(result) {
          ret = true;
          killed = true;
        }
      }
    }
    else {
      // it's good, so we can dfs it
      if(e.to != parent) {
        bool result = dfs(e.to, curr, killed);
        if(result) {
          ret = true;
          killed = true;
        }
      }
    }
  }

  if(!killed) {
    // this is safe for now, add it
    good.push_back(curr);
  }
  return ret;
}

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  cin >> n;
  adj.resize(n);
  //good.assign(n, true);
  for(int i = 0; i<n-1; ++i) {
    int a, b, c; cin >> a >> b >> c;
    a--; b--;
    adj[a].push_back({b, c});
    adj[b].push_back({a, c});
  }

  dfs(0, -1, false);

  cout << good.size() << endl;
  sort(good.begin(), good.end());
  for(int i = 0; i<good.size(); ++i) {
    cout << good[i]+1 << "\n";
  }
}
