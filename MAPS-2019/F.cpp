#include <bits/stdc++.h>

using namespace std;

int main() {
  int t; cin >> t;
  double PI = 3.14159265358979323;
  while(t--) {
    double r; int n; cin >> r >> n;

    double ret = 0;
    if(n >= 1) {
      // First iteration has one circle
      ret += PI * r * r;
      r /= 2;
    }
    if(n >= 2) {
      // Second iteration has four more circles
      ret += 4 * PI * r * r;
      r /= 2;
    }
    double num_circles = 4; // it doesn't work if this is an int instead of a double!
    while(n >= 3) {
      // Each iteration has three times as many circles
      num_circles *= 3;
      ret += num_circles * PI * r * r;
      r /= 2;

      n--;
    }
    cout << fixed << setprecision(15) << ret << endl; // make sure you have enough precision
  }
}
