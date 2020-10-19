#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  int n;
  double m, tct, tr;
  while(cin >> n >> m >> tct >> tr) {
    double t = (n * tr + (n-1) * tct);
    t /= 2;
    cout << fixed << setprecision(2) << 4.9 * t*t << endl;
  }
}
