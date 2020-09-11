#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  int n;
  while(cin >> n) {
    cout << n << ":\n";
    for(int i = 2; i<n; ++i) {
      if(n % (2*i-1) == 0) {
        cout << " " << i << "," << i-1 << "\n";
      }

      if((n - i) % (2*i-1) == 0) {
        cout << " " << i << "," << i-1 << "\n";
      }

      if(n % i == 0) {
        cout << " " << i << "," << i << "\n";
      }
    }
  }
}
