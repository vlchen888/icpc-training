#include <bits/stdc++.h>

using namespace std;

struct Point {
  double x;
  double y;
};

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  double L, W, H; cin >> L >> W >> H;
  double x, y, a; cin >> x >> y >> a;
  a = (a/180.)*3.14159265358979;

  Point a1; a1.x = x; a1.y = y;
  Point a2; a2.x = (x + H*cos(a)); a2.y = y + H*sin(a);

  bool intersect = false;
  double eps = 0.0001;
  intersect = intersect || (a1.x < 0-eps || a2.x < 0-eps);
  intersect = intersect || (a1.y < 0-eps || a2.y < 0-eps);
  intersect = intersect || (a1.x > W+eps || a2.x > W+eps);
  intersect = intersect || (a1.y > L+eps || a2.y > L+eps);

  cout << (intersect ? "NO" : "YES") << endl;
}
