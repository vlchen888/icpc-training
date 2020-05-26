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
        int N; cin >> N;
        vi A(N);
        for (int i = 0; i < N; i++) cin >> A[i];
        sort(all(A));
        int k = N;
        while (k > 0 && A[k-1] > k) k--;
        cout << k+1 << '\n';
    }
}
