#include <bits/stdc++.h>

using namespace std;

int n;
vector<string> grid;

struct pos {
  int x;
  int y;
};

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  cin >> n;
  grid.resize(n);
  for(int i = 0; i<n; ++i) cin >> grid[i];

  pos start;
  for(int i = 0; i<n; ++i) {
    for(int j = 0; j<n; ++j) {
      if(grid[i][j] == '@') {
        start.x = i;
        start.y = j;
      }
    }
  }

  deque<pair<pos, int> > q;
  q.push_back(make_pair(start, 0));
  int dp[n][n][1<<10];
  for(int i = 0; i<n; ++i) {
    for(int j = 0; j<n; ++j) {
      for(int k = 0; k<(1<<10); ++k) {
        dp[i][j][k] = INT_MAX;
      }
    }
  }
  dp[start.x][start.y][0] = 0;

  while(!q.empty()) {
    pair<pos, int> curr = q.front(); q.pop_front();
    pos cp = curr.first;
    int mask = curr.second;
    //cout << cp.x << " " << cp.y << " " << mask << " " << dp[cp.x][cp.y][mask] << endl;
    if(grid[cp.x][cp.y] == '$') {
      cout << dp[cp.x][cp.y][mask] << endl;
      return 0;
    }
    if(grid[cp.x][cp.y] >= 'a' && grid[cp.x][cp.y] <= 'z') {
      int which = grid[cp.x][cp.y] - 'a';
      if((mask >> which) & 1) {}
      else {
        dp[cp.x][cp.y][mask + (1<<which)] = dp[cp.x][cp.y][mask];
        q.push_front(make_pair(cp, mask + (1<<which)));
      }
    }
    vector<pair<int, int> > dirs;
    dirs.push_back(make_pair(1, 0));
    dirs.push_back(make_pair(-1, 0));
    dirs.push_back(make_pair(0, 1));
    dirs.push_back(make_pair(0, -1));
    for(int i = 0; i<4; ++i) {
      pos next = cp;
      next.x += dirs[i].first;
      next.y += dirs[i].second;
      if(next.x < 0 || next.x >= n || next.y < 0 || next.y >= n) continue;
      if(grid[next.x][next.y] == '#') continue;
      if(grid[next.x][next.y] >= 'A' && grid[next.x][next.y] <= 'Z') {
        int which = grid[next.x][next.y] - 'A';
        if((mask >> which) & 1) {}
        else continue;
      }
      if(dp[next.x][next.y][mask] != INT_MAX) continue;

      //cout << " " << next.x << " " << next.y << endl;
      dp[next.x][next.y][mask] = dp[cp.x][cp.y][mask]+1;
      q.push_back(make_pair(next, mask));
    }
  }

  cout << "IMPOSSIBLE" << endl;
}
