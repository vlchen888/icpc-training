#include <bits/stdc++.h>

using namespace std;

int n;
double dp[301][301][301];

double go(int c1, int c2, int c3) {
  if(dp[c1][c2][c3] != -1) return dp[c1][c2][c3];

  // Don't forget the base case :')
  if(c1 == c2 && c2 == c3 && c3 == 0) return 0;

  double p = (1.0 * n - c1 - c2 - c3) / (1.0 * n);
  double ret = p / (1-p);
  if(c1 != 0) {
    ret += (1.0 * c1) / (c1+c2+c3) * (1 + go(c1-1, c2, c3));
  }
  if(c2 != 0) {
    ret += (1.0 * c2) / (c1+c2+c3) * (1 + go(c1+1, c2-1, c3));
  }
  if(c3 != 0) {
    ret += (1.0 * c3) / (c1+c2+c3) * (1 + go(c1, c2+1, c3-1));
  }
  dp[c1][c2][c3] = ret;
  return ret;
}

int main() {
  // J: which dish has how many pieces isn't important,
  // the only thing that matters is the count of 1 pieces,
  // 2 pieces, and 3 pieces

  // so there's like 300^3 states, and 3 transitions to
  // worry about, which should be totally fine

  // the problem is that you have to deal with self-loops
  // so if there's a probability p of returning to the same
  // state (rolling a dish with no pieces on it), that'll
  // increase the expected rolls for sure
  // okay so E(rolls) = p*(1+E(rolls)) + (1-p)*(R)
  // where R is calculated by proceeding with the DP normally
  // E(rolls) * (1-p) = p + (1-p) * R
  // E(rolls) = p / 1-p + R
  // tada
  // let's see if this makes sense: if you've got 299 empty
  // and one dish with one sushi on it, then E(rolls) =
  // (299/300) / (1/300) + R = 299 + 1 = 300... I guess that makes
  // sense?  each time, there's a 1/300 chance, so you'd
  // expect about 300 rolls before you hit the one you want


  cin.tie(0);
  cin.sync_with_stdio(0);

  cin >> n;
  int c[4] = {0, 0, 0, 0};
  for(int i = 0; i<n; ++i) {
    int cc; cin >> cc;
    c[cc]++;
  }
  for(int i = 0; i<=300; ++i) {
    for(int j = 0; j<=300; ++j) {
      for(int k = 0; k<=300; ++k) {
        dp[i][j][k] = -1;
      }
    }
  }

  cout << fixed << setprecision(14) << go(c[1], c[2], c[3]) << endl;
}
