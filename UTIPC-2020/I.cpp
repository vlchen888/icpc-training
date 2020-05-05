#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  int n; cin >> n;
  int f[n], g[n];
  vector<int> countf(1e5+1, 0), countg(1e5+1, 0);
  unordered_set<int> uniqf, nuniqf, uniqg, nuniqg; // best names 2k20
  unordered_map<int, unordered_set<int> > fback, gback;
  for(int i = 0; i<n; ++i) {
    cin >> f[i];
    countf[f[i]]++;
    fback[f[i]].insert(i);
  }
  for(int i = 0; i<n; ++i) {
    cin >> g[i];
    countg[g[i]]++;
    gback[g[i]].insert(i);
  }
  for(int i = 0; i<1e5+1; ++i) {
    if(countf[i] > 0) {
      if(countf[i] == 1) uniqf.insert(i);
      else               nuniqf.insert(i);
    }
    if(countg[i] > 0) {
      if(countg[i] == 1) uniqg.insert(i);
      else               nuniqg.insert(i);
    }
  }
  int w; cin >> w;
  for(int i = 0; i<w; ++i) {
    string s; cin >> s;
    if(s == "YES") {
      if(i % 2 == 0) {
        for(auto y : nuniqf) {
          for(auto x : fback[y]) {
            countg[g[x]]--;
            gback[g[x]].erase(x);
            if(countg[g[x]] == 1) {
              nuniqg.erase(g[x]);
              uniqg.insert(g[x]);
            }
            if(countg[g[x]] == 0) {
              uniqg.erase(g[x]);
            }
          }
          fback.erase(y);
          countf[y] = 0;
        }
        nuniqf.clear();
      }
      else {
        for(auto y : nuniqg) {
          for(auto x : gback[y]) {
            countf[f[x]]--;
            fback[f[x]].erase(x);
            if(countf[f[x]] == 1) {
              nuniqf.erase(f[x]);
              uniqf.insert(f[x]);
            }
            if(countf[f[x]] == 0) {
              uniqf.erase(f[x]);
            }
          }
          gback.erase(y);
          countg[y] = 0;
        }
        nuniqg.clear();
      }
    }
    else {
      if(i % 2 == 0) {
        for(auto y : uniqf) {
          for(auto x : fback[y]) {
            countg[g[x]]--;
            gback[g[x]].erase(x);
            if(countg[g[x]] == 1) {
              nuniqg.erase(g[x]);
              uniqg.insert(g[x]);
            }
            if(countg[g[x]] == 0) {
              uniqg.erase(g[x]);
            }
          }
          fback.erase(y);
          countf[y] = 0;
        }
        uniqf.clear();
      }
      else {
        for(auto y : uniqg) {
          for(auto x : gback[y]) {
            countf[f[x]]--;
            fback[f[x]].erase(x);
            if(countf[f[x]] == 1) {
              nuniqf.erase(f[x]);
              uniqf.insert(f[x]);
            }
            if(countf[f[x]] == 0) {
              uniqf.erase(f[x]);
            }
          }
          gback.erase(y);
          countg[y] = 0;
        }
        uniqg.clear();
      }
    }
  }

  vector<int> poss;
  for(int i = 0; i<n; ++i) {
    if(countf[f[i]] > 0 && countg[g[i]] > 0) {
      poss.push_back(i);
    }
  }
  if(poss.size() == 0) {cout << -1 << endl;}
  else {
    for(auto x : poss) {
      cout << x+1 << " ";
    }
    cout << endl;
  }
}
