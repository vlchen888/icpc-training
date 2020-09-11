#include <bits/stdc++.h>
#include "helpers.h"

using namespace std;

int main() {
  ofstream in1("../in/reduced1.in");
  ofstream out1("../out/reduced1.out");

  for(int i = 2; i<=36; ++i) {
    vector<vector<int> > square;
    if(i < 10) square = generateSmall(i);
    else       square = generateLarge(i);
    reduce(square);
    assert(isLatin(square) && isReduced(square));
    writeSquare(square, in1);
    writeSquareType(square, out1);
  }
}
