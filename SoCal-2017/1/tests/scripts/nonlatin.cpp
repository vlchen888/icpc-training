#include <bits/stdc++.h>
#include "helpers.h"

using namespace std;

int main() {
  ofstream in1("../in/nonlatin1.in");
  ofstream out1("../out/nonlatin1.out");

  for(int i = 2; i<=36; ++i) {
    vector<vector<int> > square;
    if(i < 10) square = generateSmall(i);
    else       square = generateLarge(i);

    if(rand() % 2 == 0) {
      reduce(square);
    }

    if(rand() % 2 == 0) {
      // Small aberration
      square[rand() % i][rand() % i] = rand() % i;
    }
    else {
      // Large aberration
      for(int j = 0; j<i; ++j) {
        square[rand() % i][rand() % i] = rand() % i;
      }
    }

    writeSquare(square, in1);
    writeSquareType(square, out1);
  }
}
