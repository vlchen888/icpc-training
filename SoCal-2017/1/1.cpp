#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  int n;
  while(cin >> n) {
    string csquare[n];
    for(int i = 0; i<n; ++i) {
      cin >> csquare[i];
    }
    int square[n][n];
    for(int i = 0; i<n; ++i) {
      for(int j = 0; j<n; ++j) {
        if(csquare[i][j] >= 'A' && csquare[i][j] <= 'Z') {
          square[i][j] = csquare[i][j] - 'A' + 10;
        }
        else {
          square[i][j] = csquare[i][j] - '0';
        }
      }
    }

    // check the ith row and column together
    bool works = true;
    for(int i = 0; i<n; ++i) {
      set<int> row, col;
      for(int j = 0; j<n; ++j) {
        if(row.find(square[i][j]) != row.end()) {
          works = false;
        }
        row.insert(square[i][j]);
        if(col.find(square[j][i]) != col.end()) {
          works = false;
        }
        col.insert(square[j][i]);
      }
    }

    if(!works) {
      cout << "No" << endl;
    }
    else {
      // is it reduced?
      bool reduced = true;
      for(int i = 0; i<n; ++i) {
        if(square[i][0] != i) reduced = false;
        if(square[0][i] != i) reduced = false;
      }
      
      if(reduced) {
        cout << "Reduced" << endl;
      }
      else {
        cout << "Not Reduced" << endl;
      }
    }
  }
}
