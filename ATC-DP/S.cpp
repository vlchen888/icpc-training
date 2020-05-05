#include <bits/stdc++.h>

using namespace std;

long long MOD = 1e9+7;
int main() {
  // S: just seems like a standard DP where you keep track of the
  // residues
  // |K|D states, 10 transitions?
  // 10^7 should totally be fine
  // oh wait, the fact that it has to be less than K (which isn't
  // just 10^x)
  // more annoying, but _should_ be fine
  // like split it up into cases?

  cin.tie(0);
  cin.sync_with_stdio(0);
  string k; cin >> k;
  int d; cin >> d;
  long long nomatch[k.length()][d], match[k.length()][d];
  for(int i = 0; i<k.length(); ++i) {
    for(int j = 0; j<d; ++j) {
      nomatch[i][j] = 0;
      match[i][j] = 0;
    }
  }

  for(int i = 0; i<(k[0]-'0'); ++i) {
    // Very important to take the mod in here!
    nomatch[0][i%d]++;
  }
  match[0][(k[0]-'0')%d]++;

  for(int i = 1; i<k.length(); ++i) {
    for(int j = 0; j<d; ++j) {
      for(int l = 0; l<=9; ++l) {
        // Don't forget to mod the result as you go
        nomatch[i][(j+l)%d] = (nomatch[i][(j+l)%d] + nomatch[i-1][j])%MOD;
        if(l < (k[i]-'0'))
          nomatch[i][(j+l)%d] = (nomatch[i][(j+l)%d] + match[i-1][j])%MOD;
      }
      match[i][(j+k[i]-'0')%d] = (match[i][(j+k[i]-'0')%d] + match[i-1][j])%MOD;
    }
  }
  // off by 1 because it includes 0, so add MOD-1
  cout << (match[k.length()-1][0] + nomatch[k.length()-1][0]+MOD-1)%MOD << endl;
}
