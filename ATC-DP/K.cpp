#include <bits/stdc++.h>

using namespace std;

int main() {
  // K: right off the bat, it feels like it would require
  // some sort of bitmask DP, but with 2^100 states, that's clearly
  // wrong...
  //
  // oh wow I really misread that, it's not that you can't
  // reuse an element of A
  //
  // so this should be just a DP with good and bad states
  // 10^5 states, 100 transitions: 10^7, which is totally fast
  // enough


  cin.tie(0);
  cin.sync_with_stdio(0);

  int n, k; cin >> n >> k;
  int a[n];
  for(int i = 0; i<n; ++i) {
    cin >> a[i];
  }

  bool dp[k+1];
  // 0 is a bad state; in other words, player 2 would win
  // if you started the game with 0 stone
  dp[0] = false;
  for(int i = 1; i<=k; ++i) {
    // i is good if you can go to any bad state; bad otherwise
    bool can_go_bad = false;
    for(int j = 0; j<n; ++j) {
      if(a[j] <= i && !dp[i-a[j]]) can_go_bad = true;
    }
    dp[i] = can_go_bad;
  }
  cout << (dp[k] ? "First" : "Second") << endl;
}
