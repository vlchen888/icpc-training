#include <bits/stdc++.h>

using namespace std;

struct P {
  double x;
  double y;
};
vector<P> pts;

typedef pair<int, int> nx;

double slope(int a, int b) {
  P i = pts[a];
  P j = pts[b];
  if(j.x < i.x) {
    // Reflect across both x and y axis
    j.y = i.y + (i.y - j.y);
    j.x = i.x + (i.x - j.x);
  }
  double dy = j.y - i.y;
  double dx = j.x - i.x;
  if(dx == 0) return 100;
  //cout << dy << " " << dx << " " << dy/dx << " " << atan(dy/dx) << endl;
  return atan(dy/dx);
}

const double PI = 3.14159265358979323;

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  int n; cin >> n;
  pts.resize(n);
  for(int i = 0; i<n; ++i) {
    cin >> pts[i].x >> pts[i].y;
  }

  vector<vector<nx> > next(n, vector<nx>(n));
  vector<vector<double> > next_ang(n, vector<double>(n));
  for(int i = 0; i<n; ++i) {
    // Sort points in angle order around i
    vector<pair<double, int> > ord;
    for(int j = 0; j<n; ++j) {
      if(i == j) continue;
      ord.push_back(make_pair(slope(i, j), j));
    }
    sort(ord.rbegin(), ord.rend());

    for(int j = 0; j<ord.size(); ++j) {
      nx a, b, c, d;
      int next_pos = ord[j].second;
      a = make_pair(i, next_pos);
      b = make_pair(ord[(j+1)%ord.size()].second, i);
      next[a.first][a.second] = b;
      next_ang[a.first][a.second] = ord[j].first - ord[(j+1)%ord.size()].first;
      if(next_ang[a.first][a.second] < 0) next_ang[a.first][a.second] += PI;
    }
  }

  int ret = 0;
  bool seen[n][n];
  for(int i = 0; i<n; ++i) {
    for(int j = 0; j<n; ++j) {
      seen[i][j] = false;
    }
  }
  for(int i = 0; i<n; ++i) {
    for(int j = 0; j<n; ++j) {
      if(i == j) continue;

      nx start;
      start = make_pair(i, j);
      double ang = 0;
      if(!seen[start.first][start.second]) {
        nx curr = start;
        unordered_map<int, int> count;
        do {
          if(false && n == 1000) {
            cout << curr.first << " " << curr.second << endl;
            cout << slope(curr.first, curr.second) << endl;
            cout << ang << endl;
          }
          count[curr.second]++;
          ret = max(ret, count[curr.second]);
          curr = next[curr.first][curr.second];
          ang += next_ang[curr.first][curr.second];
          seen[curr.first][curr.second] = true;

        } while(ang <= 6 || curr != start);
        //cout << curr.first << " " << curr.second << endl;
        //cout << ang << endl;
      }
    }
  }
  cout << ret << endl;
}
