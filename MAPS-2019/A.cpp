#include <bits/stdc++.h>

using namespace std;

int main() {
  // This problem is about sorting -- it might seem like it can be solved
  // just by calling C++'s sort() function on the decimal f/b ratios.
  // However, the biggest difficulty here is dealing with precision.  Simply dividing the front gear ratio by the back one is
  // going to give the wrong answer -- instead, to work only in integers, we implement a comparator that cross-multiplies.  Comparing
  // (f1, b1) to (f2, b2) can be done by looking at f1*b2 vs. f2*b1.

  int f, b; cin >> f >> b;

  vector<long long> front(f), back(b);
  for(int i = 0; i<f; ++i) cin >> front[i];
  for(int i = 0; i<b; ++i) cin >> back[i];

  // Generate all pairs of gears
  vector<pair<long long, long long> > pairs;
  for(int i = 0; i<f; ++i) {
    for(int j = 0; j<b; ++j) {
      pair<long long, long long> fb = make_pair(front[i], back[j]);
      pairs.push_back(fb);
    }
  }

  auto sortRule = [] (pair<long long, long long> const& p1, pair<long long, long long> const& p2) -> bool {
    if(p1.first * p2.second != p2.first * p1.second) return (p1.first * p2.second < p2.first * p1.second);
    return p1.first < p2.first;
  };

  sort(pairs.begin(), pairs.end(), sortRule);

  for(int i = 0; i<f*b; ++i) {
    cout << "(" << pairs[i].first << "," << pairs[i].second << ")" << endl;
  }
}
