#include <bits/stdc++.h>

using namespace std;

int main() {
  // 100^4 is 100 million, so just trying all pairs of spies and safe houses is fast enough

  int n; cin >> n;
  vector<pair<int, int> > spies, houses;
  for(int i = 0; i<n; ++i) {
    string row; cin >> row;
    for(int j = 0; j<n; ++j) {
      if(row[j] == 'H') houses.push_back(make_pair(i, j));
      if(row[j] == 'S') spies.push_back(make_pair(i, j));
    }
  }

  int max_dist = 0;
  for(int i = 0; i<spies.size(); ++i) {
    int current_dist = 300; // How far does this spy need to travel?
    for(int j = 0; j<houses.size(); ++j) {
      current_dist = min(current_dist, abs(spies[i].first - houses[j].first) + abs(spies[i].second - houses[j].second));
    }
    max_dist = max(max_dist, current_dist);
  }
  cout << max_dist << endl;
}
