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
    ll X1, Y1, X2, Y2;
    cin >> X1 >> Y1 >> X2 >> Y2;
    X2 -= (X1 - 1);
    Y2 -= (Y1 - 1);
    if (X2 <= Y2) swap(X2, Y2);
    ll A;
    if (X2 == Y2) {
        A = (Y2-1)*Y2/2 + (Y2-2)*(Y2-1)/2 + 1;
    } else {
        A = (Y2-1) * Y2 + (X2-Y2-1) * (Y2 - 1) + 1;
    }
    cout << A << "\n";
}

int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}
