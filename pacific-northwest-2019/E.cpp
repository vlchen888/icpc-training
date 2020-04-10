#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair< int, int > pii;
typedef vector< int > vi;

const ll MOD = 11092019;

int counts[26];
int main() {
    string s; cin >> s;
    for (char c : s) counts[c - 'a']++;
    ll ans = 1;
    for (int i = 0; i < 26; i++) {
        ans = (ans * (counts[i] + 1)) % MOD;
    }
    cout << ans << '\n';
}
