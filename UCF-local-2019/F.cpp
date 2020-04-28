#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;
const int MX = 7;
int grid[MX][MX];
vector<pi> gt[MX][MX], lt[MX][MX], indexes;
vector<int> row, col;
int n;

bool dfs(int idx) {
  if(idx == indexes.size()) return true;
  pi curr = indexes[idx];
  int i = curr.first;
  int j = curr.second;

  for(int k = 1; k<=n; ++k) {
    if((row[i] >> k) & 1) continue;
    if((col[j] >> k) & 1) continue;

    bool works = true;
    for(auto pp : gt[i][j]) {
      if(grid[pp.first][pp.second] <= k && grid[pp.first][pp.second] != -1) works = false;
    }
    for(auto pp : lt[i][j]) {
      if(grid[pp.first][pp.second] >= k && grid[pp.first][pp.second] != -1) works = false;
    }
    if(!works) continue;

    row[i] += (1 << k);
    col[j] += (1 << k);
    grid[i][j] = k;
    if(dfs(idx+1)) return true;
    row[i] -= (1 << k);
    col[j] -= (1 << k);
    grid[i][j] = -1;
  }
  return false;
}

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  cin >> n;
  row.assign(n, 0);
  col.assign(n, 0);
  string input_grid[2*n-1];
  for(int i = 0; i<2*n-1; ++i) {
    cin >> input_grid[i];
  }
  for(int i = 0; i<n; ++i) {
    for(int j = 0; j<n; ++j) {
      if(input_grid[2*i][2*j] == '-') {
        grid[i][j] = -1;
        indexes.push_back(make_pair(i, j));
      }
      else {
        grid[i][j] = input_grid[2*i][2*j] - '0';
        row[i] += (1 << grid[i][j]);
        col[j] += (1 << grid[i][j]);
      }
    }
  }
  for(int i = 0; i<n; ++i) {
    for(int j = 0; j<n-1; ++j) {
      if(input_grid[2*i][2*j+1] == '.') continue;
      
      if(input_grid[2*i][2*j+1] == '>') {
        lt[i][j].push_back(make_pair(i, j+1));
        gt[i][j+1].push_back(make_pair(i, j));
      }
      if(input_grid[2*i][2*j+1] == '<') {
        gt[i][j].push_back(make_pair(i, j+1));
        lt[i][j+1].push_back(make_pair(i, j));
      }
    }
  }
  for(int i = 0; i<n-1; ++i) {
    for(int j = 0; j<n; ++j) {
      if(input_grid[2*i+1][2*j] == '.') continue;
      
      if(input_grid[2*i+1][2*j] == 'v') {
        lt[i][j].push_back(make_pair(i+1, j));
        gt[i+1][j].push_back(make_pair(i, j));
      }
      if(input_grid[2*i+1][2*j] == '^') {
        gt[i][j].push_back(make_pair(i+1, j));
        lt[i+1][j].push_back(make_pair(i, j));
      }
    }
  }

  dfs(0);
  for(int i = 0; i<n; ++i) {
    for(int j = 0; j<n; ++j) {
      cout << grid[i][j];
    }
    cout << endl;
  }
}
