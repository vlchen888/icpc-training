#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair< int, int > pii;
typedef vector< int > vi;

const double PI = 3.141592653589793238462643383;
int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    cout << fixed << setprecision(8);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        n *= 2;
        double ans = 1 / tan(PI / n);
        cout << ans << "\n";
    }
}
