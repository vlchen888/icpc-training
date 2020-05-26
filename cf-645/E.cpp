#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair< int, int > pii;
typedef vector< int > vi;


void solve() {
    ll N; cin >> N;
    ll M = (N/2);
    vector<ll> A(N);
    if (N % 2) M++;
    for (ll i = 0; i < M; i++) cin >> A[i];
    ll X; cin >> X;
    for (ll i = M; i < N; i++) A[i] = X;
    vector<ll> G(M);
    for (ll i = 0; i < M; i++) {
        G[i] = X - A[i];
        if (i > 0) G[i] += G[i-1];
    }
    vector<ll> P(N);
    for (ll i = 0; i < N; i++) { P[i] = A[i]; if (i > 0) P[i] += P[i-1]; }
    int i = 0;
    ll Z = 0;
    for (ll K = N; K >= M; K--) {
        if (P[K-1] + Z > 0) {
            cout << K << '\n';
            return;
        }
        Z = min(Z, G[i++]);
    }
    cout << "-1\n";
}

int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    solve();
}
