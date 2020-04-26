#include <bits/stdc++.h>

using namespace std;
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair< int, int > pii;
typedef vector< int > vi;

struct hole{
    int x, y, z, r;
};

long double vol_above(int x, int y, int z, int R, long double z0) {
    long double PI = 3.141592653589793238462643383279502884197169399375105820974944592307816406286;
    z0 -= z;
    long double sphere = 4./3*PI*R*R*R;
    if (z0 < 0) {
        return (sphere - vol_above(x, y, 0, R, -z0));
    }
    if (z0 > R) {
        return 0;
    }
    long double h = R - z0;
    long double val = 1./3.*PI*h*h*(3*R-h);
    return val;
}
long double vol(hole a, long double z0, long double z1) {
    return (vol_above(a.x, a.y, a.z, a.r, z0) - vol_above(a.x, a.y, a.z, a.r, z1)) * (long double)(1e-9);
}

long double tot_vol(vector<hole> holes, long double z0, long double z1) {
    long double sum = 0.0;
    for (hole h : holes) {
        sum+= vol(h, 1000 * z0, 1000 * z1);
    }
    // cout << z0 << ',' << z1 << ',' << 1e4 * (z1 - z0) - sum << endl;
    return (long double)(1e4) * (z1 - z0) - sum;
}
int main() {
    int n, s;
    long double vol_per_slice;

    /* hole x = {0, 0, 1000, 1000}; */
    /* double v = vol_above(x, 500); */
    /* cerr << v << endl; */
    cin >> n >> s;
    vector<hole> holes;
    for (int i = 0; i < n; i++) {
        hole h;
        cin >> h.r >> h.x >> h.y >> h.z;
        holes.push_back(h);
    }

    vol_per_slice = (tot_vol(holes, 0, 100))/(long double)(s); // cubic millimemeters

    long double prev_z = 0.0;
    for (int i = 0; i < s; i++) {
        long double low = prev_z, high = 1e2, mid;
        while(high - low > 1e-8) {
            mid = (low+high)/2;
            long double vol = tot_vol(holes, prev_z, mid);
            if (vol >= vol_per_slice) {
                high = mid;
            } else {
                low = mid;
            }
        }
        cout << fixed << setprecision(8);
        cout << mid - prev_z << '\n';
        prev_z = mid; 
    }
}
