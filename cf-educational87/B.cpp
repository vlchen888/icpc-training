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
        string s; cin >> s;
        int best_len = s.length()+1;
        int L = 0, R = 0;
        vi counts = {0, 0, 0};
        while (L < s.length()) {
            while (R < s.length() && (!counts[0] || !counts[1] || !counts[2])) 
                counts[s[R++] - '1']++;
            if (counts[0] && counts[1] && counts[2]) best_len = min(best_len, R-L);
            counts[s[L] - '1']--;
            L++;
        }
        cout << (best_len == s.length()+1 ? 0 : best_len) << '\n';
    }
}
