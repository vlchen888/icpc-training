#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair< int, int > pii;
typedef vector< int > vi;

int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    int t; cin >> t;
    while (t--) {
        ll a, b, c, d; cin >> a >> b >> c >> d;
        if (a <= b) {
            cout << b << "\n";
            continue;
        }
        if (d >= c) {
            cout << "-1\n";
            continue;
        }
        ll ok = ceil(double(a-b)/double(c-d));
        ll ans = b + ok * c;
        cout << ans << "\n";
    }
}
