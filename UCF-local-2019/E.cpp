#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  int n, k; cin >> n >> k;

  vector<bool> isprime(2499001, true);
  vector<bool> isprime2(2499001, true);
  isprime[0] = false;
  isprime[1] = false;
  for(int i = 2; i<=n; ++i) {
    if(isprime[i]) {
      for(int j = 2; i*j<2499000; ++j) {
        isprime[i*j] = false;
      }
    }
  }

  isprime2[0] = false;
  isprime2[1] = false;
  for(int i = 2; i<2499000; ++i) {
    if(isprime2[i]) {
      for(int j = 2; i*j<2499000; ++j) {
        isprime2[i*j] = false;
      }
    }
  }

  int ctr = 0;
  for(int i = n+1; i<=2499000; ++i) {
    if(isprime[i] && !isprime2[i]) ctr++;
    if(ctr == k) {
      cout << i << endl;
      return 0;
    }
  }
}
