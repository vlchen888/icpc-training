#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  int n, p; cin >> n >> p;
  map<string, vector<int> > mp;
  for(int i = 0; i<n-1; ++i) {
    string s; cin >> s;
    mp[s].push_back(i);
  }
  int deck_size; cin >> deck_size;
  vector<pair<int, string> > deck(deck_size);
  for(int i = 0; i<deck_size; ++i) {
    cin >> deck[i].first >> deck[i].second;
  }

  vector<int> pos(p, -1);
  int curr_turn = 0;
  for(int i = 0; i<=20000; ++i) {
    pair<int, string> card = deck[i%deck_size];
    switch(card.first) {
      case 1:
        {
        auto it = upper_bound(mp[card.second].begin(), mp[card.second].end(), pos[curr_turn]);
        if(it == mp[card.second].end()) {
          cout << curr_turn+1 << endl;
          return 0;
        }
        pos[curr_turn] = mp[card.second][it - mp[card.second].begin()];
        break;
        }
      case 2:
        {
        for(int j = 0; j<2; ++j) {
          auto it = upper_bound(mp[card.second].begin(), mp[card.second].end(), pos[curr_turn]);
          if(it == mp[card.second].end()) {
            cout << curr_turn+1 << endl;
            return 0;
          }
          pos[curr_turn] = mp[card.second][it - mp[card.second].begin()];
        }
        break;
        }
      case 3:
        {
        pos[curr_turn] = mp[card.second][0];
        break;
        }
    }

    curr_turn = (curr_turn + 1) % p;
  }
}
