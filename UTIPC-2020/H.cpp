#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  string grid[8];
  for(int i = 0; i<8; ++i) cin >> grid[i];

  set<int> r, c;
  for(int i = 0; i<8; ++i) {
    for(int j = 0; j<8; ++j) {
      if(grid[i][j] == 'R') {r.insert(i); c.insert(j);}
    }
  }
  int ret = 0;
  for(int i = 0; i<8; ++i) {
    for(int j = 0; j<8; ++j) {
      if(r.find(i) == r.end() && c.find(j) == c.end()) ret++;
    }
  }

  cout << ret << endl;
}
