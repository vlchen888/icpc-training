#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair< int, int > pii;
typedef vector< int > vi;

int p, a, b, c, d, n;

double price(int k) {
    return p *(sin(a*k+b) + cos(c*k+d)+d);
}

int main() {
    cin >> p >> a >> b >> c >> d >> n;
    double m = price(1);
    double max_diff = 0;
    for (int k = 2; k <= n; k++) {
        double x = price(k);
        max_diff = max(max_diff, m - x);
        m = max(m, x);
    }
    printf("%.8f\n", max_diff);
}
