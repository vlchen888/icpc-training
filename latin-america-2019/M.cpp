#include <bits/stdc++.h>

using namespace std;

int main() {
  int n, x; cin >> n >> x;

  int a[n];
  for(int i = 0; i<n; ++i) {
    cin >> a[i];
  }

  int max_seen = 0;
  for(int i = 0; i<n; ++i) {
    // start from the ith viewpoint
    int prev_viewpoint = a[i];
    int curr_seen = 0;
    for(int j = i; j<n; ++j) {
      if(a[j] - prev_viewpoint > x) break;
      curr_seen++;
      prev_viewpoint = a[j];
    }
    max_seen = max(max_seen, curr_seen);
  }
  cout << max_seen << endl;
}
