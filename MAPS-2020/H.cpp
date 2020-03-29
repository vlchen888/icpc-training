#include <bits/stdc++.h>

using namespace std;

int main() {
  long long c, n, m; cin >> c >> n >> m;

  vector<long long> count(c+1, 0);
  for(long long i = 0; i<n; ++i) {
    long long curr; cin >> curr;
    count[curr]++;
  }

  vector<long long> total(51, 0);
  for(long long i = 0; i<51; ++i) {
    // Count up
    for(long long j = 0; j<=c; ++j) {
      total[i] += count[j];
    }

    // Double
    vector<long long> next_count(c+1, 0);
    for(long long j = 0; j<=c; ++j) {
      long long ct = count[j];
      if(2*j <= c) {
        next_count[2*j] += ct;
      }
      else {
        next_count[j] += 2*ct;
      }
    }
    count = next_count;
  }

  for(int i = 0; i<m; ++i) {
    int day; cin >> day;
    cout << total[day] << endl;
  }
}
