#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  int n; cin >> n;
  int f[n], g[n];
  unordered_map<int, unordered_set<int> > fm, gm;
  for(int i = 0; i<n; ++i) {
    cin >> f[i];
    fm[f[i]].insert(i);
  }
  for(int i = 0; i<n; ++i) {
    cin >> g[i];
    gm[g[i]].insert(i);
  }
  int w; cin >> w;
  for(int i = 0; i<w; ++i) {
    string s; cin >> s;
    if(s == "YES") {
      if(i % 2 == 0) {
        vector<int> to_delete;
        for(auto it : fm) {
          if(it.second.size() != 1) {
            to_delete.push_back(it.first);
            for(auto x : it.second) {
              gm[g[x]].erase(gm[g[x]].find(x));
            }
          }
        }
        for(auto tod : to_delete) {
          fm.erase(fm.find(tod));
        }
      }
      else {
        vector<int> to_delete;
        for(auto it : gm) {
          if(it.second.size() != 1) {
            to_delete.push_back(it.first);
            for(auto x : it.second) {
              fm[f[x]].erase(fm[f[x]].find(x));
            }
          }
        }
        for(auto tod : to_delete) {
          gm.erase(gm.find(tod));
        }
      }
    }
    else {
      if(i % 2 == 0) {
        vector<int> to_delete;
        for(auto it : fm) {
          if(it.second.size() == 1) {
            to_delete.push_back(it.first);
            for(auto x : it.second) {
              gm[g[x]].erase(gm[g[x]].find(x));
            }
          }
        }
        for(auto tod : to_delete) {
          fm.erase(fm.find(tod));
        }
      }
      else {
        vector<int> to_delete;
        for(auto it : gm) {
          if(it.second.size() == 1) {
            to_delete.push_back(it.first);
            for(auto x : it.second) {
              fm[f[x]].erase(fm[f[x]].find(x));
            }
          }
        }
        for(auto tod : to_delete) {
          gm.erase(gm.find(tod));
        }
      }
    }
  }

  vector<int> cands;
  for(auto it : fm) {
    for(auto x : it.second) {
      cands.push_back(x);
    }
  }
  if(cands.size() == 0) {cout << -1 << endl;}
  else {
    sort(cands.begin(), cands.end());
    for(auto x : cands) {
      cout << x+1 << " ";
    }
    cout << endl;
  }
}
