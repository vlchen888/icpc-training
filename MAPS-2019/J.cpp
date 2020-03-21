#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
#define trav(x, v) for(auto x : v)
#define sz(v) (v).size()
#define all(v) v.begin(), v.end()
#define rep(i, a, b) for(int i = (a); i<(b); ++i)

bool find(int j, vector<vi>& g, vi& btoa, vi& vis) {
	if (btoa[j] == -1) return 1;
	vis[j] = 1; int di = btoa[j];
	trav(e, g[di])
		if (!vis[e] && find(e, g, btoa, vis)) {
			btoa[e] = di;
			return 1;
		}
	return 0;
}
int dfsMatching(vector<vi>& g, vi& btoa) {
	vi vis;
	rep(i,0,sz(g)) {
		vis.assign(sz(btoa), 0);
		trav(j,g[i])
			if (find(j, g, btoa, vis)) {
				btoa[j] = i;
				break;
			}
	}
	return sz(btoa) - (int)count(all(btoa), -1);
}

int main() {
  // It's just a bipartite matching problem.  Grab the source from KACTL: https://github.com/kth-competitive-programming/kactl/blob/master/content/graph/DFSMatching.h
  int n, m; cin >> n >> m;

  vector<vector<int> > adj(n);
  for(int i = 0; i<n; ++i) {
    int count; cin >> count;
    adj[i].resize(count);
    for(int j = 0; j<count; ++j) {
      cin >> adj[i][j];
      adj[i][j]--; // The algorithm wants everything 0-indexed
    }
  }
  vector<int> btoa(m, -1);
  cout << dfsMatching(adj, btoa) << endl;
}
