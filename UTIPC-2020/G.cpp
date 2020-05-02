#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair< int, int > pii;
typedef vector< int > vi;

// flow
template<class T> T edmondsKarp(vector<unordered_map<int, T>>& graph, int source, int sink) {
	assert(source != sink);
	T flow = 0;
	vi par(sz(graph)), q = par;

	for (;;) {
		fill(all(par), -1);
		par[source] = 0;
		int ptr = 1;
		q[0] = source;

		rep(i,0,ptr) {
			int x = q[i];
			for (auto e : graph[x]) {
				if (par[e.first] == -1 && e.second > 0) {
					par[e.first] = x;
					q[ptr++] = e.first;
					if (e.first == sink) goto out;
				}
			}
		}
		return flow;
out:
		T inc = numeric_limits<T>::max();
		for (int y = sink; y != source; y = par[y])
			inc = min(inc, graph[par[y]][y]);

		flow += inc;
		for (int y = sink; y != source; y = par[y]) {
			int p = par[y];
			if ((graph[p][y] -= inc) <= 0) graph[p].erase(y);
			graph[y][p] += inc;
		}
	}
}
//

int N;
int main() {
    cin >> N;
    int A = N, J = N+1;
    vector<unordered_map<int, ll>> graph(N+2);
    ll cost = 0;
    for (int i = 0; i < N; i++) {
        ll c, a, j; cin >> c >> a >> j;
        cost += (c - a - j);
        graph[A][i] = j;
        graph[i][J] = a;
    }
    int B; cin >> B;
    for (int x = 0; x < B; x++) {
        int a, b; ll c;
        cin >> a >> b >> c;
        a--;
        b--;
        graph[a][b] += c;
        graph[b][a] += c;
    }
    ll ans = edmondsKarp(graph, A, J);
    cout << cost + ans << '\n';
}
