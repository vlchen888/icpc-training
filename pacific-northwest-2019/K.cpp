#include <bits/stdc++.h>

using namespace std;
long long n, m, q;
vector<long long> sizes;
vector<long long> version;
vector<vector<long long> > datas;
vector<vector<pair<long long, long long> > > updates;
vector<pair<pair<long long, long long>, long long> > prints;

typedef vector<long long> vi;
const long long inf = 1e18;
struct Node {
	Node *l = 0, *r = 0;
	long long lo, hi, mset = inf, madd = 0, val = -inf;
	Node(long long lo,long long hi):lo(lo),hi(hi){} // Large interval of -inf
	Node(vi& v, long long lo, long long hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			long long mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = max(l->val, r->val);
		}
		else val = v[lo];
	}
	long long query(long long L, long long R) {
		if (R <= lo || hi <= L) return -inf;
		if (L <= lo && hi <= R) return val;
		push();
		return max(l->query(L, R), r->query(L, R));
	}
	void set(long long L, long long R, long long x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) mset = val = x, madd = 0;
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void add(long long L, long long R, long long x) {
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
			long long mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
		if (mset != inf)
			l->set(lo,hi,mset), r->set(lo,hi,mset), mset = inf;
		else if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
};

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  cin >> n >> m >> q;

  sizes.resize(m);
  datas.resize(m);
  updates.resize(m);
  version.assign(m, 0);
  for(long long i = 0; i<m; ++i) {
    // size, and then each piece of data
    cin >> sizes[i];
    datas[i].resize(sizes[i]);
    for(long long j = 0; j<sizes[i]; ++j) {
      cin >> datas[i][j];
    }
  }

  vector<long long> temp(n, -1);
  Node* segtree = new Node(temp, 0, n);

  for(long long qq = 0; qq<q; ++qq) {
    long long type; cin >> type;
    switch(type) {
      long long i, p, l, r;
      case 1:
        {
        // Load
        cin >> i >> p;
        i--; p--;
        long long data_and_version = i * q + version[i];
        long long data_and_version_and_start = data_and_version * n + p;
        segtree->set(p, p+sizes[i], data_and_version_and_start);
        break;
        }
      case 2:
        {
        // Print
        cin >> p;
        p--;
        // This segtree implementation queries in range [l, r).....
        long long data_and_version_and_start = segtree->query(p, p+1);
        if(data_and_version_and_start == -1) {
          // Nothing loaded here yet
          prints.push_back(make_pair(make_pair(-1, -1), -1));
        }
        else {
          // gross.................
          // which data? there's m possibilities
          // which version? there's q possibilities
          // which start location? there's n possibilities
          long long data_and_version = data_and_version_and_start / n;
          long long data = data_and_version / q;
          long long version = data_and_version % q;
          long long start = data_and_version_and_start % n;
          prints.push_back(make_pair(make_pair(data, version), p - start));
        }
        break;
        }
      case 3:
        // Update
        cin >> i >> l >> r;
        i--; l--; r--;
        version[i]++;
        updates[i].push_back(make_pair(l, r));
        break;
    }
  }

  vector<vector<vector<long long> > > sorted_prints;
  vector<Node*> vst(m);
  map<pair<pair<long long, long long>, long long>, long long> print_answers;
  sorted_prints.resize(m);
  for(long long i = 0; i<m; ++i) {
    sorted_prints[i].resize(version[i] + 1);
    vst[i] = new Node(datas[i], 0, sizes[i]);
  }
  for(long long i = 0; i<prints.size(); ++i) {
    if(prints[i].first.first == -1)
      print_answers[prints[i]] = 0;
    else
      sorted_prints[prints[i].first.first][prints[i].first.second].push_back(prints[i].second);
  }
  for(long long i = 0; i<updates.size(); ++i) {
    for(long long j = 0; j<=updates[i].size(); ++j) {
      // Naive bruteforce update for now, segtree later
      for(long long k = 0; k<sorted_prints[i][j].size(); ++k) {
        long long answer = vst[i]->query(sorted_prints[i][j][k], sorted_prints[i][j][k]+1);
        print_answers[make_pair(make_pair(i, j), sorted_prints[i][j][k])] = (answer % 256);
      }

      if(j == updates[i].size()) break;

      vst[i]->add(updates[i][j].first, updates[i][j].second+1, 1);
      /*
      for(int k = updates[i][j].first; k <= updates[i][j].second; ++k) {
        datas[i][k] = (datas[i][k]+1) % 256;
      }
      */
    }
  }

  for(long long i = 0; i<prints.size(); ++i) {
    cout << print_answers[prints[i]] << endl;
  }
}
