#include <bits/stdc++.h>

using namespace std;

long long MOD = 1e9+7;

struct block {
  int w;
  int s;
  long long v;
};

int main() {
  // X: sort, and then do a DP like LIS (i.e. involving bsearch)
  int n; cin >> n;
  vector<block> blocks(n);
  for(int i = 0; i<n; ++i) {
    cin >> blocks[i].w >> blocks[i].s >> blocks[i].v;
  }
  sort(blocks.begin(), blocks.end(), 
      [](const block& b1, const block& b2) {
        // magic!
        return b1.s+b1.w < b2.s+b2.w;
      });
  long long dp[n+1][10000+2];
  for(int i = 0; i<n+1; ++i) {
    for(int j = 0; j<1e4+2; ++j) {
      dp[i][j] = -1;
    }
  }
  dp[0][0] = 0;
  long long ret = 0;
  for(int i = 0; i<n; ++i) {
    for(int j = 0; j<1e4+2; ++j) {
      if(dp[i][j] == -1) continue;
      // don't take this block
      dp[i+1][j] = max(dp[i+1][j], dp[i][j]);
      ret = max(ret, dp[i+1][j]);

      // do take this block
      if(j <= blocks[i].s) {
        ret = max(ret, dp[i][j] + blocks[i].v);
        if(j+blocks[i].w < 1e4+2) {
          dp[i+1][j+blocks[i].w] = max(dp[i+1][j+blocks[i].w], dp[i][j] + blocks[i].v);
        }
      }
    }
  }

  cout << ret << endl;
}
