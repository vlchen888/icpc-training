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
    ll N, X; cin >> N >> X;
    vector<ll> DT(N);
    for (int i = 0; i < N; i++) cin >> DT[i];
    vector<ll> D(3*N);
    for (int i = 0; i < 3*N; i++) D[i] = DT[i % N];
    vector<ll> prefix(3*N, 0), sumsq(3*N, 0);
    prefix[0] = D[0];
    sumsq[0] = D[0] * (D[0]+1) / 2;
    for (int i = 1; i < 3*N; i++) {
        prefix[i] = prefix[i-1] + D[i];
        sumsq[i] = sumsq[i-1] + D[i]*(D[i]+1)/2;
    }
    ll best = 0;
    for (int i = N; i < 2*N; i++) {
        // first
        int L = i, R = 3*N-1;
        while (L < R) {
            int M = (L+R)/2;
            if (prefix[M] - prefix[i-1] < X) {
                L = M+1;
            } else {
                R = M;
            }
        }
        ll V = 0, Y = X;
        if (L-1 >= i) {
            V += (sumsq[L-1] - sumsq[i-1]);
            Y -= (prefix[L-1] - prefix[i-1]);
        }
        V += Y*(Y+1)/2;
        best = max(best, V);

        // last
        L = 0, R = i;
        while (L < R) {
            int M = 1 + (L+R)/2;
            if (prefix[i] - prefix[M-1] < X) {
                R = M-1;
            } else {
                L = M;
            }
        }
        V = 0, Y = X;
        if (L+1 <= i) {
            V += (sumsq[i] - sumsq[L]);
            Y -= (prefix[i] - prefix[L]);
        }
        V += D[L] * (D[L] + 1) / 2 - (D[L] - Y) * (D[L] - Y + 1) / 2;
        best = max(best, V);
    }
    cout << best << '\n';
}

int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    solve();
}
