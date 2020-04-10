#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair< int, int > pii;
typedef vector< int > vi;

const int MAXN = 100000;
ll tax[MAXN + 1];
int par[MAXN + 1];
ll parwt[MAXN + 1];
vi toposort;

// node, edge weight
vector<pii> adj[MAXN + 1], children[MAXN + 1];



ll ccounts[MAXN + 1], cdown[MAXN + 1], cans[MAXN + 1];
unordered_map<int, ll>  cnot[MAXN + 1];

ll wcounts[MAXN + 1], wdown[MAXN + 1], wans[MAXN + 1];
unordered_map<int, ll>  wnot[MAXN + 1];

int visited[MAXN + 1];
void dfs(int x) {
    visited[x] = 1;
    toposort.push_back(x);
    for (pii p : adj[x]) {
        int y, wt;
        tie(y, wt) = p;
        if (!visited[y]) {
            par[y] = x;
            parwt[y] = wt;
            children[x].push_back({y, wt});
            dfs(y);
        }
    }
}

int main() {
    int n; cin >> n;
    int tottax = 0;
    for (int i = 1; i <= n; i++) {
        cin >> tax[i];
        tottax += tax[i];
    }
    for (int i = 0; i < n; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    dfs(1);
    for (int i = n - 1; i >= 0; i--) {
        int u = toposort[i];
        ccounts[u] = 1;
        wcounts[u] = tax[u];
        for (pii p : children[u]) {
            int v = p.first;
            ll wt = p.second;
            ccounts[u] += ccounts[v];
            cdown[u] += (cdown[v] + ccounts[v] * wt);

            wcounts[u] += wcounts[v];
            wdown[u] += (wdown[v] + wcounts[v] * wt);
        }
    }
    for (int i = 0; i < n; i++) {
        int u = toposort[i];
        for (pii p : children[u]) {
            int x = p.first; ll wt = p.second;
            cnot[u][x] = cnot[par[u]][u] 
                + (n - ccounts[u]) * parwt[u]
                + cdown[u]
                - cdown[x]
                -ccounts[x]*wt;

            wnot[u][x] = wnot[par[u]][u] 
                + (tottax - wcounts[u]) * parwt[u]
                + wdown[u]
                - wdown[x]
                -wcounts[x]*wt;
        }
    }
    for (int u = 1; u <= n; u++) {
       cans[u] = cnot[par[u]][u] + (n - ccounts[u]) * parwt[u] + cdown[u];
       wans[u] = wnot[par[u]][u] + (tottax - wcounts[u]) * parwt[u] + wdown[u];
       /* cerr << u << " " << cans[u] << " " << wans[u] << '\n'; */
       ll ans = cans[u] * tax[u] + wans[u];
       cout << ans << '\n';
    }
}
