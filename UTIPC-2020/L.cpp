#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair< int, int > pii;
typedef vector< int > vi;

/* ll gcd(ll x, ll y) return __gcd(x, y); */
ll gcd(ll x, ll y) {
    if (x > y) return gcd(y, x);
    if (x == 0) return y;
    return gcd(y % x, x);
}

ll N, M;

int main() {
    cin >> N >> M;
    ll G = 0;
    for (int i = 0; i < N; i++) {
        ll a; cin >> a;
        a--;
        while ((a & 1) == 0) a >>= 1;
        if (G == 0) {
            G = a;
        } else {
            G = gcd(G, a);
        }
    }
    ll ccount = 0;
    for (ll x = 1; x < sqrt(G) + 1; x++) {
        if (G % x == 0) {
            if (x > G/x) continue;
            ll y = x;
            while (M - y > 0) {
                ccount += M - y;
                y <<= 1;
            }
            if (x != G/x) {
                ll y = G/x;
                while (M - y > 0) {
                    ccount += M - y;
                    y <<= 1;
                }
            }
        }
    }
    cout << ccount << '\n';
}
