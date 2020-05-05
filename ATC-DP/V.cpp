#include <bits/stdc++.h>

using namespace std;

int n;
vector<vector<int> > adj;
long long MOD;
vector<long long> colorings;
vector<vector<long long> > colorings_without;

void dfs1(int curr, int p) {
  colorings[curr] = 1;
  for(int i = 0; i<adj[curr].size(); ++i) {
    int next = adj[curr][i];
    if(next == p) continue;
    dfs1(next, curr);
    colorings[curr] = (colorings[curr] * (1+colorings[next]))%MOD;
    // colorings[next] is the number of colorings of next's
    // subtree assuming that next is colored, so add 1 to
    // account for the possibility that it isn't colored
  }

  // now this is gross...
  colorings_without[curr].assign(adj[curr].size(), 1);
  long long last = 1;
  vector<long long> l, r;
  for(int i = 0; i<adj[curr].size(); ++i) {
    int next = adj[curr][i];
    if(next == p) continue;
    last = (last * (1+colorings[next]))%MOD;
    l.push_back(last);
  }
  r.resize(l.size());
  last = 1;
  int counter = r.size()-1;
  for(int i = adj[curr].size()-1; i>=0; --i) {
    int next = adj[curr][i];
    if(next == p) continue;
    last = (last * (1+colorings[next]))%MOD;
    r[counter--] = last;
  }
  counter = 0;
  for(int i = 0; i<adj[curr].size(); ++i) {
    int next = adj[curr][i];
    if(next == p) continue;
    colorings_without[curr][counter] = ((counter==0?1:l[counter-1]) * (counter==r.size()-1?1:r[counter+1])) % MOD;
    counter++;
  }
  // blehhhhhhhhhhhhhhhhhhh
}

void dfs2(int curr, int p, long long running) {
  // now for the up direction
  // uh oh...  we can't do modular inverses because M isn't
  // necessarily a prime
  running++;
  colorings[curr] = (colorings[curr] * running) % MOD;
  int counter = 0;
  for(int i = 0; i<adj[curr].size(); ++i) {
    int next = adj[curr][i];
    if(next == p) continue;
    dfs2(next, curr, (running * colorings_without[curr][counter])%MOD);
    counter++;
  }
}

int main() {
  // V: another tree DP, but probably with some amount of
  // rerooting
  //
  // so my reading of the constraint is that the black vertices
  // need to form a contiguous block
  // which means that if you start out by painting v black,
  // you can compute something via dp
  // and then multiply them all together (one per child node) to
  // get the number of colorings
  // the down direction is the easy one, that's just one dfs
  // and then going up is more of a problem

  cin.tie(0);
  cin.sync_with_stdio(0);
  cin >> n >> MOD;
  adj.resize(n);
  colorings.resize(n);
  colorings_without.resize(n);
  for(int i = 0; i<n-1; ++i) {
    int u, v; cin >> u >> v;
    u--; v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  dfs1(0, -1);
  dfs2(0, -1, 0);

  for(int i = 0; i<n; ++i) {
    cout << colorings[i] << endl;
  }

}
