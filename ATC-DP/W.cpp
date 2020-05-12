#include <bits/stdc++.h>

using namespace std;

#define sz(v) (int)v.size()
#define rep(i, a, b) for(int i = (a); i<(b); ++i)
typedef vector<long long> vi;
const long long inf = 1e17;
struct Node {
	Node *l = 0, *r = 0;
	long long lo, hi, mset = inf, madd = 0, val = -inf;
	Node(int lo,int hi):lo(lo),hi(hi){} // Large interval of -inf
	Node(vi& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = max(l->val, r->val);
		}
		else val = v[lo];
	}
	long long query(int L, int R) {
		if (R <= lo || hi <= L) return -inf;
		if (L <= lo && hi <= R) return val;
		push();
		return max(l->query(L, R), r->query(L, R));
	}
	void set(int L, int R, long long x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) mset = val = x, madd = 0;
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void add(int L, int R, long long x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			if (mset != inf) mset += x;
			else madd += x;
			val += x;
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
		if (mset != inf)
			l->set(lo,hi,mset), r->set(lo,hi,mset), mset = inf;
		else if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
};

int main() {
  // W is a tricky segtree (RMQ) problem
  // dp[i] = max value for prefix of 0 through i with ith
  // position on, and then the recurrence is:
  // and then dp[i] = max over all j<i of dp[j] + the total
  // reward of all intervals starting in [j+1, i] and ending in
  // [i, ...]

  cin.tie(0);
  cin.sync_with_stdio(0);
  int n, m; cin >> n >> m;
  priority_queue<pair<int, pair<long long, int> > > start, end;
  for(int i = 0; i<m; ++i) {
    int l, r; long long a;
    cin >> l >> r >> a;
    //l--; r--;
    start.push(make_pair(-l, make_pair(a, r)));
    end.push(make_pair(-r, make_pair(a, l)));
  }
  vector<long long> v(n+1, 0);
  Node rmq(v, 0, n+1);

  long long ret = 0;
  for(int i = 1; i<=n; ++i) {
    while(start.size() && start.top().first == -i) { // lots of dots
      // Entering an interval
      long long a = start.top().second.first;
      int l = -start.top().first;
      start.pop();
      rmq.add(0, l, a);
    }

    ret = max(ret, rmq.query(0, i));
    rmq.set(i, i+1, rmq.query(0, i));

    while(end.size() && end.top().first == -i) { // lots of dots
      // Exiting an interval
      long long a = end.top().second.first;
      int l = end.top().second.second;
      end.pop();
      rmq.add(0, l, -a);
    }
  }
  cout << ret << endl;
}
