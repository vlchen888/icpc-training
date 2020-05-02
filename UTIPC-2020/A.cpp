#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair< int, int > pii;
typedef vector< int > vi;

int N, C, K;
vector<vi> cnums;

bool possible(int score) {
    for (int c = 1; c <= C; c++) {
        int slide = 0;
        int cost = 0;
        int left = 0, right = 0;
        while (right < cnums[c].size()) {
            if (cnums[c][right] < 0) {
                cost -= cnums[c][right];
            } else {
                slide += cnums[c][right];
            }
            right++;
            while (cost > K) {
                if (cnums[c][left] < 0) {
                    cost += cnums[c][left];
                } else {
                    slide -= cnums[c][left];
                }
                left++;
            }
            if (slide >= score && cost <= K) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    cin >> N >> C >> K;
    vi nums(N, 0);
    for (int i = 0; i < N; i++) cin >> nums[i];
    cnums.assign(C+1, vi());
    int currc = -1, currcount = 0;
    vi cprev(C+1, -1);
    for (int i = 0; i < N; i++) {
        int nextc = nums[i];
        if (currc == -1) {
            currc = nextc;
            currcount = 1;
        } else if (currc != nextc) {
            if (cprev[nextc] != -1) {
                cnums[nextc].push_back(-(i - cprev[nextc] - 1));
            }
            cprev[currc] = i-1;
            cnums[currc].push_back(currcount);
            currc = nextc;
            currcount = 1;
        } else {
            currcount++;
        }
    }
    cnums[currc].push_back(currcount);

    /* // debug */
    /* for (int c = 1; c <= C; c++) { */
    /*     cerr << "color " << c << endl; */
    /*     for (int x : cnums[c]) { */
    /*         cerr << x << ' '; */
    /*     } */
    /*     cerr << endl; */
    /* } */
    /* // */

    int lo = 1, hi = N + 1;
    while (lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if (possible(mid)) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    cout << lo << endl;
}
