#include <bits/stdc++.h>

using namespace std;

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

typedef Point<double> P;

bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

#define all(v) v.begin(), v.end()

vector<P> segInter(P a, P b, P c, P d) {
	auto oa = c.cross(d, a), ob = c.cross(d, b),
	     oc = a.cross(b, c), od = a.cross(b, d);
	// Checks if intersection is single non-endpoint point.
	if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
		return {(a * ob - b * oa) / (ob - oa)};
	set<P> s;
	if (onSegment(c, d, a)) s.insert(a);
	if (onSegment(c, d, b)) s.insert(b);
	if (onSegment(a, b, c)) s.insert(c);
	if (onSegment(a, b, d)) s.insert(d);
	return {all(s)};
}

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  int l, w, n, p; cin >> l >> w >> n >> p;
  vector<pair<P, P> > lines(n);
  for(int i = 0; i<n; ++i) {
    cin >> lines[i].first.x >> lines[i].first.y >> lines[i].second.x >> lines[i].second.y;
  }

  while(p--) {
    P ll, rr;
    cin >> ll.x >> ll.y >> rr.x >> rr.y;
    P mid;
    mid.x = (ll.x + rr.x) / 2;
    mid.y = (ll.y + rr.y) / 2;
    vector<pair<P, P> > edges(4);

    P lr;
    lr.y = ll.y;
    lr.x = rr.x;
    P rl;
    rl.y = rr.y;
    rl.x = ll.x;
    edges[0].first = ll;
    edges[0].second = lr;
    edges[1].first = lr;
    edges[1].second = rr;
    edges[2].first = rr;
    edges[2].second = rl;
    edges[3].first = rl;
    edges[3].second = ll;
    
    vector<int> cands;
    for(int i = 0; i<n; ++i) {
      cands.push_back(i);
    }
    bool works = false;
    for(auto i : cands) {
      P f = lines[i].first;
      P s = lines[i].second;
      bool f_in = f.x >= ll.x && f.x <= rr.x && f.y >= ll.y && f.y <= rr.y;
      bool s_in = s.x >= ll.x && s.x <= rr.x && s.y >= ll.y && s.y <= rr.y;
      
      if(!f_in && s_in) swap(f, s);
      vector<P> points_to_try;
      if(f_in && s_in) {
        // try f and s
        points_to_try.resize(2);
        points_to_try[0] = f;
        points_to_try[1] = s;
      }
      else if(!f_in && !s_in){
        // both are phone boundaries, or none at all
        for(auto edge : edges) {
          vector<P> inters = segInter(s, f, edge.first, edge.second);
          for(auto p : inters) {
            points_to_try.push_back(p);
          }
        }
      }
      else {
        // try f and intersection with phone boundary
        points_to_try.push_back(f);

        for(auto edge : edges) {
          vector<P> inters = segInter(mid, s, edge.first, edge.second);
          for(auto p : inters) {
            points_to_try.push_back(p);
          }
        }
      }

      for(int iter = 0; iter<points_to_try.size(); ++iter) {
        P c = points_to_try[iter];
        P vec = mid-c;
        P flip = mid + vec*10000000; // fun
        for(auto j : cands) {
          vector<P> inter = segInter(mid, flip, lines[j].first, lines[j].second);
          for(auto k : inter) {
            if(k.x >= ll.x && k.x <= rr.x && k.y >= ll.y && k.y <= rr.y) works = true;
          }
        }
      }
    }
    cout << (works ? "No" : "Yes") << endl;
  }
}
