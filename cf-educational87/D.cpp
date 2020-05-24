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
    int N, Q; cin >> N >> Q;
    int A[N], K[Q];
    for (int i = 0; i < N; i++) cin >> A[i];
    for (int i = 0; i < Q; i++) cin >> K[i];
    int L = 1, R = N+1;
    while (L < R) {
        int M = (L+R)/2;
        int counts[] = {0, 0};
        for (int i = 0; i < N; i++) counts[A[i] <= M ? 0 : 1]++;
        for (int i = 0; i < Q; i++) {
            if (K[i] < 0) {
                counts[-K[i] <= counts[0] ? 0 : 1]--;
            } else {
                counts[K[i] <= M ? 0 : 1]++;
            }
        }
        if (counts[0]) {
            R = M;
        } else {
            L = M+1;
        }
    }
    if (L == N+1) {
        cout << "0\n";
    } else {
        cout << L << "\n";
    }
}
