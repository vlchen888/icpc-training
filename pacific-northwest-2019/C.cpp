#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair< int, int > pii;
typedef vector< int > vi;

int N, M;
vi adj[100001];
int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vi visited(N + 1, 0), dist(N + 1, 0);
    queue<int> q;
    q.push(1);
    visited[1] = 1;
    while (!q.empty()) {
        int next = q.front(); q.pop();
        if (next == N) {
            cout << dist[next] - 1<< endl;
            return 0;
        }
        for (int b : adj[next]) {
            if (!visited[b]) {
                visited[b] = 1;
                dist[b] = dist[next] + 1;
                q.push(b);
            }
        }
    }
}
