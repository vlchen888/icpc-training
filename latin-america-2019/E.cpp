/* 
 * kactl template
 * vlchen
 * 01/02/20
 */

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
    string B;
    ll S;
    cin >> B >> S;
    vector<ll> p;
    int n = B.size();
    int i = 0;
    while (i < n) {
        if (B[i] != 'P') {
            i++;
            continue;
        }
        int j = i + 1;
        while (j < n && B[j] == 'P') {
            j++;
        }
        p.push_back(j - i);
        i = j;
    }

    // check begin and end equal
    if (B[0] == 'P' && B[n - 1] == 'P' && p.size() > 1) {
        ll x = p[p.size() - 1];
        p.pop_back();
        p[0] += x;
    }
    // edge case
    if (p.size() == 1 && p[0] == n) {
        cout << 0 << endl;
        return 0 ;
    }
    ll ans = n * S;
    for (int i = 0; i < p.size(); i++) {
        ll m = p[i];
        ll sub;
        if (S <= m) {
            sub = (m * S - S * (S - 1) / 2);
        } else {
            sub = m * (m + 1) / 2;
        }
        ans -= sub;
    }
    cout << ans << endl;
}
