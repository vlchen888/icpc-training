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
    int n, k; cin >> n >> k;
    vi x(n+1, 0), last(k+1,0);
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
        last[x[i]] = i;
    }
    vi sub;
    set<int> s;
    for (int i = 1; i <= n; i++) {
        if (s.find(x[i]) != s.end()) continue;
        while (!sub.empty() && sub.back() > x[i]) {
            if (i < last[sub.back()]) {
                s.erase(sub.back());
                sub.pop_back();
            } else {
                break;
            }
        }
        s.insert(x[i]);
        sub.push_back(x[i]);
    }
    for (int z : sub) {
        cout << z << " ";
    }
    cout << "\n";
}
