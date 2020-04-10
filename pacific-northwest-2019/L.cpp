#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair< int, int > pii;
typedef vector< int > vi;

int x[25], a[25];
int n, k;

bool dfs(int curr) {
    if (curr == k) {
        vi y(n, 0);
        for (int c = 0; c < k; c++) for(int d = 0; d < k; d++) {
            int i = c+d;
            assert(a[c] >= 0 && a[d] >= 0);
            y[i] = (y[i] + a[c]*a[d]) % 10;
        }
        for (int i = 0; i < n; i++) {
            if (x[i] != y[i]) {
                return false;
            }
        }
        return true;
    }
    int sum = 0;
    int free = -1, coeff = 0;
    for (int c = 0; c < k; c++) {
        for (int d = 0; d < k; d++) {
            if (c + d == curr) {
                if (a[c] >= 0 && a[d] >= 0) {
                    sum = (sum + a[c] * a[d]) % 10;
                } else {
                    assert(a[c]>=0 || a[d]>=0);
                    if (a[c]>=0) {
                        free = d; coeff = a[c];
                    } else {
                        free = c; coeff = a[d];
                    }
                }
            }
        }
    }
    assert(free != -1);
    int desired = (x[curr] + 10 - sum) % 10;
    for (int d = 0; d < 10; d++) {
        if ( (2 * d * coeff) % 10 == desired) {
            a[free] = d;
            if (dfs(curr + 1)) return true;
        }
    }
    a[free] = -1;
    return false;
}

int main() {
    string s; cin >> s;
    n = s.length();
    for (int i = 0; i < s.length(); i++) x[i] = s[i] - '0';
    if (n % 2 == 0) {
        cout << "-1\n";
        return 0;
    }
    k = (n+1)/2;
    for (int i = 0; i < k; i++) a[i] = -1;
    switch(x[0]) {
        case 1: 
            a[0] = 1; break;
        case 4:
            a[0] = 2; break;
        case 9:
            a[0] = 3; break;
        case 6:
            a[0] = 4; break;
        case 5:
            a[0] = 5; break;
        default:
            cout << "-1\n";
            return 0;
    }
    bool success = dfs(1);
    if (!success) {
        cout << "-1\n";
        return 0;
    }
    for (int i = 0; i < k; i++) {
        cout << a[i];
    }
    cout << '\n';
}
