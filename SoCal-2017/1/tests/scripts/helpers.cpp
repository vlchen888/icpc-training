#include <bits/stdc++.h>

using namespace std;

vector<vector<int> > generateSmall(int n) {
  // from rosetta code: uniformly random latin square, but too slow for n>~10
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  auto g = default_random_engine(seed);

  vector<vector<int>> latin;
  for (int i = 0; i < n; ++i) {
    vector<int> inner;
    for (int j = 0; j < n; ++j) {
      inner.push_back(j);
    }
    latin.push_back(inner);
  }
  // first row
  shuffle(latin[0].begin(), latin[0].end(), g);

  // middle row(s)
  for (int i = 1; i < n - 1; ++i) {
    bool shuffled = false;

    while (!shuffled) {
      shuffle(latin[i].begin(), latin[i].end(), g);
      for (int k = 0; k < i; ++k) {
        for (int j = 0; j < n; ++j) {
          if (latin[k][j] == latin[i][j]) {
            goto shuffling;
          }
        }
      }
      shuffled = true;

shuffling: {}
    }
  }

  // last row
  for (int j = 0; j < n; ++j) {
    vector<bool> used(n, false);
    for (int i = 0; i < n - 1; ++i) {
      used[latin[i][j]] = true;
    }
    for (int k = 0; k < n; ++k) {
      if (!used[k]) {
        latin[n - 1][j] = k;
        break;
      }
    }
  }

  return latin;
}

vector<vector<int> > generateLarge(int n) {
  // simple method for generating larger squares, although they'll all
  // be in the same isotopy class
  vector<vector<int> > square(n, vector<int>(n));
  for(int j = 0; j<n; ++j) {
    for(int k = 0; k<n; ++k) {
      square[j][k] = (j+k)%n;
    }
  }

  // Random swaps to create randomly permuted array
  for(int j = 0; j<5*n; ++j) {
    if(rand() % 2 == 0) {
      // swap two columns
      int c1 = rand() % n;
      int c2 = rand() % n;
      for(int k = 0; k<n; ++k) {
        swap(square[k][c1], square[k][c2]);
      }
    }
    else {
      // swap two rows
      int r1 = rand() % n;
      int r2 = rand() % n;
      for(int k = 0; k<n; ++k) {
        swap(square[r1][k], square[r2][k]);
      }
    }
  }

  // Also randomly permute the numbers
  vector<int> new_order(n);
  for(int i = 0; i<n; ++i) {
    new_order[i] = i;
  }
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  auto g = default_random_engine(seed);
  shuffle(new_order.begin(), new_order.end(), g);

  return square;
}

void reduce(vector<vector<int> > &square) {
  int n = square.size();
  sort(square.begin(), square.end());

  vector<int> colorder(n);
  for(int i = 0; i<n; ++i) {
    colorder[i] = square[0][i];
  }
  for(int i = 0; i<n; ++i) {
    vector<int> new_row(n);
    for(int j = 0; j<n; ++j) {
      new_row[colorder[j]] = square[i][j];
    }
    square[i] = new_row;
  }
}

bool isLatin(vector<vector<int> > square) {
  int n = square.size();
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
  return works;
}

bool isReduced(vector<vector<int> > square) {
  int n = square.size();
  bool reduced = true;
  for(int i = 0; i<n; ++i) {
    if(square[i][0] != i) reduced = false;
    if(square[0][i] != i) reduced = false;
  }
  return reduced;
}

void writeSquare(vector<vector<int> > square, ofstream &out) {
  int n = square.size();
  out << n << endl;
  for(int i = 0; i<n; ++i) {
    for(int j = 0; j<n; ++j) {
      if(square[i][j] < 10) {
        out << string(1, square[i][j] + '0');
      }
      else {
        out << string(1, square[i][j] - 10 + 'A');
      }
    }
    out << "\n";
  }
}

void writeSquareType(vector<vector<int> > square, ofstream &out) {
  if(!isLatin(square)) {
    out << "No\n";
  }
  else if(isReduced(square)) {
    out << "Reduced\n";
  }
  else {
    out << "Not Reduced\n";
  }
}
