#include <bits/stdc++.h>

using namespace std;

struct factor {
  int p;
  int mult;
};

int main() {
  int k; cin >> k;
  vector<vector<factor> > ret;
  int times = 0;
  if(k % 2 == 0) k = 3*k/2+1;
  else           k = 3*(k+1)/2;
  while(ret.size() < k) {
    {
      vector<factor> one;
      factor twof;
      twof.p = 2;
      twof.mult = times;
      one.push_back(twof);
      factor threef;
      threef.p = 3;
      threef.mult = times;
      one.push_back(threef);
      ret.push_back(one);
    }
    {
      vector<factor> two;
      factor twof;
      twof.p = 2;
      twof.mult = times+1;
      two.push_back(twof);
      factor threef;
      threef.p = 3;
      threef.mult = times;
      two.push_back(threef);
      ret.push_back(two);
    }
    {
      vector<factor> three;
      factor twof;
      twof.p = 2;
      twof.mult = times;
      three.push_back(twof);
      factor threef;
      threef.p = 3;
      threef.mult = times+1;
      three.push_back(threef);
      ret.push_back(three);
    }
    times++;
  }

  cout << k << endl;
  for(int i = 0; i<k; ++i) {
    int ct = 0;
    for(int j = 0; j<ret[i].size(); ++j) {
      if(ret[i][j].mult != 0) ct++;
    }
    cout << ct << " ";
    for(int j = 0; j<ret[i].size(); ++j) {
      if(ret[i][j].mult != 0) {
        cout << ret[i][j].p << " " << ret[i][j].mult << " ";
      }
    }
    cout << endl;
  }
}
