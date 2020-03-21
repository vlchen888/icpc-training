#include <bits/stdc++.h>

using namespace std;

struct P {
  int x;
  int y;
  int z;
};

double dist(P a, P b) {
  double xsq = (a.x-b.x) * (a.x-b.x);
  double ysq = (a.y-b.y) * (a.y-b.y);
  double zsq = (a.z-b.z) * (a.z-b.z);
  return sqrt(xsq + ysq + zsq);
}

int main() {
  // It's a bitmask DP.
  int n; cin >> n;

  vector<P> points(n);
  for(int i = 0; i<n; ++i) {
    cin >> points[i].x >> points[i].y >> points[i].z;
  }

  double INF = (double)INT_MAX;
  // dp[i][j][k] represents the state:
  // i is the set of planets visited so far
  // j is which planet we're currently on
  // k is whether we just teleported, i.e. this planet's teleporter is broken
  double dp[1<<n][n][2];
  for(int i = 0; i<(1<<n); ++i) {
    for(int j = 0; j<n; ++j) {
      for(int k = 0; k<2; ++k) {
        dp[i][j][k] = INF;
      }
    }
  }

  double ret = INF;
  dp[0][0][0] = 0; // start on planet 0, with no planets visited so far, and the teleporter available
  for(int i = 0; i<(1<<n); ++i) {
    for(int j = 0; j<n; ++j) {
      for(int k = 0; k<2; ++k) {
        //cout << i << " " << j << " " << k << " " << dp[i][j][k] << endl;
        if(dp[i][j][k] == INF) continue;

        vector<int> not_visited;
        for(int l = 0; l<n; ++l) {
          if(!((i >> l) & 1)) not_visited.push_back(l);
        }

        if(not_visited.size() == 0) {
          // Do nothing
        }
        else if(not_visited.size() == 1) {
          // Go home!  We assumed above that we only use the home planet's teleporter at the start of the journey
          ret = min(ret, dp[i][j][k] + dist(points[j], points[0]));
        }
        else {
          for(int l = 1; l<not_visited.size(); ++l) {
            int to_visit = not_visited[l];
            //cout << i << " " << j << " " << k << " " << dp[i][j][k] << " " << to_visit << endl;
            int mask = i | (1<<to_visit);
            if(k == 0) {
              // We didn't use the portal to get here, so we can use it in the next step
              dp[mask][to_visit][1] = min(dp[mask][to_visit][1], dp[i][j][k]);
            }
            // Either way, we can just fly
            dp[mask][to_visit][0] = min(dp[mask][to_visit][0], dp[i][j][k] + dist(points[j], points[to_visit]));
          }
        }
      }
    }
  }
  cout << fixed << setprecision(12) << ret << endl;
}
