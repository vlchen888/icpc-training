#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  long long n;
  while(cin >> n) {
    long long togo = ((n-1)*n)/4;
    long long low = 1, high = n;
    while(low < high-1) {
      long long mid = (low+high)/2;
      long long currtogo = ((n-mid)*(n-mid+1))/2;
      if(currtogo > togo) {
        low = mid;
      }
      else {
        high = mid;
      }
    }
    cout << low << endl;
  }
}
