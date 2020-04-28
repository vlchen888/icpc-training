#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  int n, d; cin >> n >> d;
  int p[n];
  int total = 0;
  for(int i = 0; i<n; ++i) {
    cin >> p[i];
    total += p[i];
  }

  for(int i = 0; i<n; ++i) {
    cout << d/total * p[i] << endl;
  }
}
