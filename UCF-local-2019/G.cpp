#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define all(v) v.begin(), v.end()
#define trav(x, v) for(auto x : v)
#define rep(x, a, b) for(int x = (a); x < (b); ++x)
const ll INF = numeric_limits<ll>::max() / 4;
typedef vector<ll> VL;

struct MCMF {
	int N;
	vector<vi> ed, red;
	vector<VL> cap, flow, cost;
	vi seen;
	VL dist, pi;
	vector<pii> par;

	MCMF(int N) :
		N(N), ed(N), red(N), cap(N, VL(N)), flow(cap), cost(cap),
		seen(N), dist(N), pi(N), par(N) {}

	void addEdge(int from, int to, ll cap, ll cost) {
		this->cap[from][to] = cap;
		this->cost[from][to] = cost;
		ed[from].push_back(to);
		red[to].push_back(from);
	}

	void path(int s) {
		fill(all(seen), 0);
		fill(all(dist), INF);
		dist[s] = 0; ll di;

		__gnu_pbds::priority_queue<pair<ll, int>> q;
		vector<decltype(q)::point_iterator> its(N);
		q.push({0, s});

		auto relax = [&](int i, ll cap, ll cost, int dir) {
			ll val = di - pi[i] + cost;
			if (cap && val < dist[i]) {
				dist[i] = val;
				par[i] = {s, dir};
				if (its[i] == q.end()) its[i] = q.push({-dist[i], i});
				else q.modify(its[i], {-dist[i], i});
			}
		};

		while (!q.empty()) {
			s = q.top().second; q.pop();
			seen[s] = 1; di = dist[s] + pi[s];
			trav(i, ed[s]) if (!seen[i])
				relax(i, cap[s][i] - flow[s][i], cost[s][i], 1);
			trav(i, red[s]) if (!seen[i])
				relax(i, flow[i][s], -cost[i][s], 0);
		}
		rep(i,0,N) pi[i] = min(pi[i] + dist[i], INF);
	}

	pair<ll, ll> maxflow(int s, int t) {
		ll totflow = 0, totcost = 0;
		while (path(s), seen[t]) {
			ll fl = INF;
			for (int p,r,x = t; tie(p,r) = par[x], x != s; x = p)
				fl = min(fl, r ? cap[p][x] - flow[p][x] : flow[x][p]);
			totflow += fl;
			for (int p,r,x = t; tie(p,r) = par[x], x != s; x = p)
				if (r) flow[p][x] += fl;
				else flow[x][p] -= fl;
		}
		rep(i,0,N) rep(j,0,N) totcost += cost[i][j] * flow[i][j];
		return {totflow, totcost};
	}

	// If some costs can be negative, call this before maxflow:
	void setpi(int s) { // (otherwise, leave this out)
		fill(all(pi), INF); pi[s] = 0;
		int it = N, ch = 1; ll v;
		while (ch-- && it--)
			rep(i,0,N) if (pi[i] != INF)
				trav(to, ed[i]) if (cap[i][to])
					if ((v = pi[i] + cost[i][to]) < pi[to])
						pi[to] = v, ch = 1;
		assert(it >= 0); // negative cost cycle
	}
};

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  int r, c; cin >> r >> c;
  string grid[r];
  for(int i = 0; i<r; ++i) {
    cin >> grid[i];
  }

  MCMF mcmf(2*r*c+2);
  pair<int, int> B, C, F;
  for(int i = 0; i<r; ++i) {
    for(int j = 0; j<c; ++j) {
      if(grid[i][j] == 'B') B = make_pair(i, j);
      if(grid[i][j] == 'C') C = make_pair(i, j);
      if(grid[i][j] == 'F') F = make_pair(i, j);
    }
  }
  for(int i = 0; i<r; ++i) {
    for(int j = 0; j<c; ++j) {
      if(grid[i][j] == 'x') continue;

      if(i != 0 && grid[i-1][j] != 'x') {mcmf.addEdge(r*c+i*c+j, (i-1)*c+j, 1, 1);}
      if(i != r-1 && grid[i+1][j] != 'x') {mcmf.addEdge(r*c+i*c+j, (i+1)*c+j, 1, 1);}
      if(j != 0 && grid[i][j-1] != 'x') {mcmf.addEdge(r*c+i*c+j, i*c+j-1, 1, 1);}
      if(j != c-1 && grid[i][j+1] != 'x') {mcmf.addEdge(r*c+i*c+j, i*c+j+1, 1, 1);}

      mcmf.addEdge(i*c+j, r*c+i*c+j, 1, 0);
    }
  }
  // 2*r*c is source, 2*r*c+1 is sink
  mcmf.addEdge(2*r*c, B.first*c+B.second, 1, 0);
  mcmf.addEdge(2*r*c, C.first*c+C.second, 1, 0);
  mcmf.addEdge(F.first*c+F.second, 2*r*c+1, 2, 0);

  pair<ll, ll> flow = mcmf.maxflow(2*r*c, 2*r*c+1);
  if(flow.first == 2) {
    cout << flow.second << endl;
  }
  else {
    cout << -1 << endl;
  }
  // E^2 is (4*cells)^2 is 16*30^4... should be fine
}
