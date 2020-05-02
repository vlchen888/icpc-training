#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair< int, int > pii;
typedef vector< int > vi;

const ll MAXN = 1000001;
ll N, K;

vi edges[MAXN], children[MAXN];
int par[MAXN], back[MAXN];
int visited[MAXN];
ll triangles;

int newname;
void dfs(int curr) {
    assert(visited[curr] == 0);
    visited[curr] = ++newname;
    for (int next : edges[curr]) {
        if (visited[next]) {
            if (par[par[curr]] == next) {
                triangles++;
            } else {
                if (back[next] == par[curr]) triangles++;
                back[next] = curr;
            }
        } else {
            par[next] = curr;
            dfs(next);
        }
    }
}

int main() {
    cin.tie(0);
    cin.sync_with_stdio(0);
    triangles = 0;
    cin >> N >> K;
    for (int i = 0; i < K; i++) {
        int u, v; cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    for (int i = 1; i <= N; i++) {
        if (!visited[i]) dfs(i);
    }

    ll twice = 0;
    for (int i = 1; i <= N; i++) {
        ll es = edges[i].size();
        twice += es * (es-1) / 2;
    }
    twice -= 3 * triangles;
    ll once = K * (N-2) - 2*twice -3*triangles;
    ll ans = N * (N-1) * (N-2) / 6;
    ans -= (once + twice);
    cout << ans << '\n';
}
