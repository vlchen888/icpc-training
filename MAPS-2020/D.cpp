#include <bits/stdc++.h>

using namespace std;

int main() {
  int t; cin >> t;
  while(t--) {
    double n, l, d, g; cin >> n >> l >> d >> g;

    double PI = 3.141592653589;
    double circ = PI * (d*g) * (d*g);
    double rect = d*g*l*n;
    double poly = l*l*n/(4*tan(PI/n));
    //cout << circ << " " << rect << " " << poly << endl;
    cout << fixed << setprecision(12) << circ+rect+poly << endl;
  }
}
