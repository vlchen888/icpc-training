#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair< int, int > pii;
typedef vector< int > vi;


vi graph[5001];

int N, M, N1, N2, N3;

int visited[5001], color[5001];
bool tcdfs(int x, int c, vi &g0, vi &g1) {
    if (visited[x]) {
        return color[x] == c;
    }
    visited[x] = 1;
    color[x] = c;
    if (c) {g1.push_back(x);}
    else {g0.push_back(x);}
    for (int y : graph[x]) {
        bool succ = tcdfs(y, !c, g0, g1);
        if (!succ) return false;
    } 
    return true;
}

int main() {
    cin >> N >> M;
    cin >> N1 >> N2 >> N3;
    for (int i = 0; i < M; i++) {
        int u, v; cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<pair<vi, vi>> components;
    vector<pii> ok;
    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            vi g0, g1;
            bool succ = tcdfs(i, 0, g0, g1);
            if (!succ) {
                cout << "NO\n";
                return 0;
            }
            components.push_back({g0, g1});
            ok.push_back({g0.size(), g1.size()});
        }
    }
    vector<vi> DP(ok.size()+1, vi(N2+1, 0)), BT(ok.size()+1, vi(N2+1, 0));
    DP[ok.size()][0] = 1;
    for (int c = ok.size() - 1; c >= 0; c--) {
        for (int u = N2; u >= 0; u--) {
            int x, y;
            tie(x, y) = ok[c];
            if (x <= u && DP[c+1][u-x]) {
                BT[c][u] = 0;
                DP[c][u] = 1;
            }
            if (y <= u && DP[c+1][u-y]) {
                BT[c][u] = 1;
                DP[c][u] = 1;
            }
        }
    }
    if (!DP[0][N2]) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    vi colors(N+1, 0);
    int c = 0, u = N2;
    while (c < ok.size()) {
        if (BT[c][u] == 0) {
            for (int x : components[c].first) {
                colors[x] = 2;
            }
            for (int x : components[c].second) {
                colors[x] = 1;
            }
        } else {
            for (int x : components[c].first) {
                colors[x] = 1;
            }
            for (int x : components[c].second) {
                colors[x] = 2;
            }
        }
        u -= (BT[c][u] ? ok[c].second : ok[c].first);
        c++;
    }
    u = N3;
    for (int x = 1; x <= N; x++) {
        if (colors[x] == 1 && u) {
            u--;
            colors[x] = 3;
        }
    }
    for (int x = 1; x <= N; x++) cout << colors[x];
    cout << '\n';
}
