#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair< int, int > pii;
typedef vector< int > vi;

int N, K;
vi dists;
int maxdist = 0;

bool bs(int J, int &jcount) {
    int travd = 0;
    jcount = 1;
    for (int d : dists) {
        if (travd + d <= J) {
            travd += d;
            continue;
        }
        jcount++;
        assert (d <= J);
        travd = d;
    }
    return jcount >= K;
}

int main() {
    cin >> N >> K;
    int prev = 0;
    for (int i = 0; i < N; i++) {
        int next; cin >> next;
        dists.push_back(next - prev);
        maxdist = max(maxdist, next-prev);
        prev = next;
    }

    int lo = maxdist, hi = 1000001;
    int jcount;
    while (lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if (bs(mid, jcount)) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    if (bs(lo, jcount) && jcount == K) {
        cout << lo << '\n';
    } else {
        cout << "-1\n";
    }
}
