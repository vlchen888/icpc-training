#include <bits/stdc++.h>

using namespace std;

int main() {
  srand((unsigned) time(0));
  const int MOD = 10000;
  for(int chain_length = 3; chain_length < 300; ++chain_length) {
    vector<pair<int, int> > chain(chain_length);
    chain[0].first = rand() % MOD;
    chain[0].second = rand() % MOD;
    for(int i = 1; i<chain_length; ++i) {
      chain[i].first = chain[i-1].second;
      chain[i].second = rand() % MOD;
    }
    for(int i = 0; i<chain_length; ++i) {
      cout << "[" << chain[i].first << "," << chain[i].second << "]";
      if(i != chain_length-1) {
        cout << "*";
      }
      else {
        cout << endl;
      }
    }
  }
}
