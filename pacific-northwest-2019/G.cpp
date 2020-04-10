#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  int n; cin >> n;

  vector<int> starts, ends;
  vector<pair<int, int> > vert;
  for(int i = 0; i<n; ++i) {
    char hv; cin >> hv;
    int t, m, a; cin >> t >> m >> a;

    t -= a-1;
    if(hv == 'h') {
      starts.push_back(t);
      ends.push_back(t+m);
    }
    else {
      vert.push_back(make_pair(t, t+m));
    }
  }
  sort(starts.begin(), starts.end());
  sort(ends.begin(), ends.end());

  long long ret = 0;
  for(int i = 0; i<vert.size(); ++i) {
    // horiz that start before vert[i].second but minus the ones that end before or at vert[i].first
    ret += (upper_bound(starts.begin(), starts.end(), vert[i].second-1)-starts.begin()) - (upper_bound(ends.begin(), ends.end(), vert[i].first)-ends.begin());
  }
  cout << ret << endl;
}
