#include <bits/stdc++.h>

using namespace std;

#define sz(v) (int)v.size()
#define rep(i, a, b) for(int i = (a); i<(b); ++i)
struct Tree {
	typedef long long T;
	static constexpr T unit = 0;
	T f(T a, T b) { return max(a, b); } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

int main() {
  // Q looks like an RMQ type DP, but it's funky...
  // like dp[i] = max sum of beauties using flowers 0 through i
  //   and including flower i
  // so then the update is: dp[i] = max over j<i with h[j] < h[i]
  //   of dp[j] right
  // when we calculate dp[i], insert dp[i] at h[i] into
  // our RMQ data structure
  // and then when we want to find the max, we just take RMQ.query
  //   (0, h[i]) and we should be fine
  // I keep forgetting that KACTL's RMQ isn't a mutable RMQ...
  // oof

  cin.tie(0);
  cin.sync_with_stdio(0);
  int n; cin >> n;
  int h[n];
  for(int i = 0; i<n; ++i) cin >> h[i];
  long long a[n];
  for(int i = 0; i<n; ++i) cin >> a[i];
  Tree rmq(n+1);

  long long ret = 0;
  for(int i = 0; i<n; ++i) {
    long long mx = rmq.query(0, h[i]);
    long long dp = mx + a[i];
    ret = max(ret, dp);
    rmq.update(h[i], dp);
  }
  cout << ret << endl;
}
