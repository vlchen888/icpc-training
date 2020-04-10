#include <bits/stdc++.h>

using namespace std;

vector<string> grid;
vector<vector<int> > color;

void dfs(int i, int j) {
  if(i<0 || i>=grid.size()) return;
  if(j<0 || j>=grid[0].size()) return;
  if(color[i][j] != -1) return;
  color[i][j] = 0;
  if(grid[i][j] != '/') dfs(i-1, j-1);
  if(i!=grid.size()-1 && grid[i+1][j] != '\\') dfs(i+1, j-1);
  if(j!=grid[i].length()-1 && grid[i][j+1] != '\\') dfs(i-1, j+1);
  if(i!=grid.size()-1 && j!=grid[i].length()-1 && grid[i+1][j+1] != '/') dfs(i+1, j+1);
}

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  int n, m; cin >> n >> m;
  grid.resize(n+4);

  bool odd = true;
  for(int i = 0; i<n; ++i) {
    cin >> grid[i+2];
    for(int j = 0; j<m; ++j) {
      if(grid[i+2][j] == '/' && (i+2+j) % 2 == 0) {
        odd = false;
      }
      else if(grid[i+2][j] == '/' && (i+2+j) % 2 == 1) {
        odd = true;
      }
    }
  }

  for(int i = 0; i<n; ++i) {
    grid[i+2] = ".." + grid[i+2] + "..";
    if(odd) {
      // pad more
      grid[i+2] = "." + grid[i+2];
    }
  }
  grid[0] = "";
  grid[1] = "";
  grid[n+2] = "";
  grid[n+3] = "";
  for(int i = 0; i<m+4+(odd?1:0); ++i) {
    grid[0] += ".";
    grid[1] += ".";
    grid[n+2] += ".";
    grid[n+3] += ".";
  }

  int components = 0;
  color.resize(grid.size());
  for(int i = 0; i<grid.size(); ++i) {
    color[i].resize(grid[i].length());
    for(int j = 0; j<grid[i].length(); ++j) {
      if((i+j)%2 == 1) continue;
      color[i][j] = -1;
    }
  }
  for(int i = 0; i<grid.size(); ++i) {
    for(int j = 0; j<grid[i].length(); ++j) {
      if((i+j)%2 == 1) continue;
      if(color[i][j] == -1) {
        dfs(i, j);
        components++;
      }
    }
  }
  cout << components-1 << endl;
}
