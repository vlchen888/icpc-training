#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair< int, int > pii;
typedef vector< int > vi;

const double PI = 3.141592653589793238462643383;

//
template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};
//

typedef Point<double> P;
void solve() {
    int N; cin >> N; N *= 2;
    double A = 2*PI/N;
    double R = 0.5/sin(A/2);
    vector<P> pts;
    P p(R, 0);
    pts.push_back(p);
    for (int i = 1; i < N; i++) {
        p = p.rotate(A);
        pts.push_back(p);
    }
    double left = 0, right = A/2;
    double side = 10000;
    while ((right - left) > 1e-6) {
        double mid = (left+right)/2;
        double xmin = 10000, xmax = -10000, ymin = 10000, ymax = -10000;
        for (P p : pts) {
            P r = p.rotate(mid);
            xmin = min(xmin, r.x);
            xmax = max(xmax, r.x);
            ymin = min(ymin, r.y);
            ymax = max(ymax, r.y);
        }
        double xdist = xmax - xmin, ydist = ymax - ymin;
        side = min(side, max(xdist, ydist));
        if (xdist > ydist) {
            left = mid;
        } else {
            right = mid;
        }
    }
    cout << side << '\n';
}
int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    cout << fixed << setprecision(8);
    int T; cin >> T;
    while (T--) solve();
}
