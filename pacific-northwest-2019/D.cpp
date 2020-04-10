#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair< int, int > pii;
typedef vector< int > vi;

ll solve(ll A, ll B) {
    if (A <= B) return B - A;
    if (A % 2) return solve(A + 1, B) + 1;
    return solve(A / 2, B) + 1;
}

int main() {
    ll A, B;
    cin >> A >> B;
    cout << solve(A, B) << '\n';
}
