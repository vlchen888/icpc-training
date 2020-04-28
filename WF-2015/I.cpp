#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  int n, w, u, v; cin >> n >> w >> u >> v;
  double t1, t2; cin >> t1 >> t2;

  vector<pair<double, int> > events;
  for(int i = 0; i<n; ++i) {
    char ew; cin >> ew;
    int m; cin >> m;
    for(int j = 0; j<m; ++j) {
      int l, p; cin >> l >> p;
      if(ew == 'E') {
        p *= -1;
      }
      if(p < 0) continue;
      double t_start = 1.0*p/u - 1.0*(i)*w/v - 1.0*w/v;
      double t_end = 1.0*(p+l)/u - 1.0*(i)*w/v;
      events.push_back(make_pair(t_start, 1));
      events.push_back(make_pair(t_end, -1));
      //cout << t_start << " " << t_end << endl;
    }
  }

  sort(events.begin(), events.end());
  int ctr = 0;
  double ret = 0.0;
  if(events.size() == 0) {
    ret = t2-t1;
  }
  else {
    ret = max(0.0, events[0].first - t1);
    ret = max(ret, t2 - events[events.size()-1].first);
  }
  for(int i = 0; i<events.size(); ++i) {
    ctr += events[i].second;
    if(ctr == 0 && i != events.size()-1) {
      if(events[i+1].first <= t1) continue;
      if(events[i].first >= t2) continue;
      ret = max(ret, min(t2, events[i+1].first) - max(t1, events[i].first));
    }
  }
  cout << fixed << setprecision(12) << ret << endl;
}
