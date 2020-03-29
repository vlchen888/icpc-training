#include <bits/stdc++.h>

using namespace std;

int main() {
  int n; cin >> n;
  double a[n];
  for(int i = 0; i<n; ++i) cin >> a[i];
  double frac = 0.8;

  double overall = 0;
  for(int i = 0; i<n; ++i) {
    overall += 0.2 * a[i] * pow(frac, i);
  }
  cout << fixed << setprecision(12) << overall << endl;

  double avg = 0;
  for(int skip = 0; skip<n; ++skip) {
    for(int i = 0; i<n-1; ++i) {
      avg += 0.2 * a[i+(i>=skip ? 1 : 0)] * pow(frac, i) / (1.0*n);
    }
  }
  cout << fixed << setprecision(12) << avg << endl;
}
