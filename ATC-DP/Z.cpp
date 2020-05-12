#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll C;

// Adapting this linecontainer code (from kactl of course)
// to be for quadratics instead :O
// it should work for any convex (monotonic?) function

// The cost of going from i to j is dp[i] + (h_j - h_i)^2 + C
// So we need a structure where we can insert (dp[i], h_i)
// pairs and query min (in structure) of cost(, h_j)
struct Line {
	mutable ll h, dp, p;
	bool operator<(const Line& o) const { return h < o.h; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) { x->p = inf; return false; }
		if (x->h == y->h) x->p = x->dp > y->dp ? inf : -inf;
		else {
      // where do x and y intersect?
      // we have x.dp + (H - x.h)^2 = y.dp + (H - y.h)^2
      // so x.dp + H^2 - 2H x.h + x.h^2 = y.dp + H^2 - 2H y.h + y.h^2
      // so x.dp - y.dp + x.h^2 - y.h^2 = 2(x.h-y.h)H
      x->p = div(x->dp - y->dp + x->h*x->h - y->h*y->h, 2*(x->h - y->h));
    }
		return x->p >= y->p;
	}
	void add(ll dp, ll h) {
		auto z = insert({h, dp, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return (x-l.h) * (x-l.h) + l.dp + C;
	}
};

int main() {
  // Z: the N^2 DP is pretty straightforward, but you need
  // the convex hull trick to find a minimum quickly.
  //
  // DP states: dp[i] = min cost to get from 0 to i
  // dp[i] = min over j<i of dp[j] + (h_j - h_i)^2 + C

  cin.tie(0);
  cin.sync_with_stdio(0);

  long long n; cin >> n >> C;
  long long h[n];
  for(int i = 0; i<n; ++i) {
    cin >> h[i];
  }

  long long dp[n];
  for(int i = 0; i<n; ++i) {
    dp[i] = LLONG_MAX;
  }
  dp[0] = 0;
  LineContainer lc;
  lc.add(0, h[0]);

  for(int i = 1; i<n; ++i) {
    dp[i] = lc.query(h[i]);
    lc.add(dp[i], h[i]);
  }
  cout << dp[n-1] << endl;
}
